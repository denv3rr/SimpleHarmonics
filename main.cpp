// =============================================================================
// Harmonic Visualizer — Pure C++ (No GMP)
// Modular exponentiation → harmonic ASCII animation (Oscilloscope / Lissajous / Plasma)
// Cross-platform (Windows/macOS/Linux). Uses ANSI; enables VT on Windows.
// Build: g++ -std=c++17 main.cpp -O2 -o harmonic
// =============================================================================

#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
#include <cmath>
#include <atomic>
#include <cstdlib>
#include <cstdint>

#ifdef _WIN32
    #include <windows.h>
#endif

// -------------------- Types & Globals --------------------

// Aliases
using u64 = unsigned long long;

// Sequence default parameters
static u64 g_base = 2;
static u64 g_mod  = 61;
static std::vector<u64> g_seq;

// Control flags
static bool g_running = true;
static bool g_showLoadingBar = true;

// Animation default state at load time
static std::atomic<bool> g_visualRunning{false};
static int g_animMs = 10;        // frame time (ms)
static int g_canvasW = 270;      // default width
static int g_canvasH = 72;       // default height

enum class Mode { Oscilloscope = 1, Lissajous = 2, Plasma = 3 };
static Mode g_mode = Mode::Oscilloscope;

// -------------------- ANSI helpers --------------------
static inline void enableVT()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}
static inline void ansi_clear()       { std::cout << "\x1b[2J\x1b[H"; }
static inline void ansi_hide_cursor(bool hide) { std::cout << (hide ? "\x1b[?25l" : "\x1b[?25h"); }

// -------------------- UI bits --------------------
static void displayLoadingBar(int progress, int total)
{
    if (total <= 0) return;
    int barWidth = 30;
    int pos = (progress * barWidth) / total;
    std::cout << " [";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos) std::cout << "\x1b[32m=\x1b[0m";
        else if (i == pos) std::cout << "\x1b[32m>\x1b[0m";
        else std::cout << ' ';
    }
    int pct = (100 * progress) / total;
    std::cout << "] " << std::setw(3) << pct << "% ";
    std::cout.flush();
}

// -------------------- Math: mulmod & modexp (64-bit, overflow-safe) --------------------
static inline u64 mulmod(u64 a, u64 b, u64 m)
{
#if defined(__GNUC__) || defined(__clang__)
    return (u64)(((__uint128_t)a * (__uint128_t)b) % m);
#else
    // Fallback for compilers w/o __int128 (kept simple; m should be reasonably small)
    // Double-and-add under modulus to avoid overflow.
    u64 res = 0;
    a %= m; b %= m;
    while (b)
    {
        if (b & 1) { res = (res + a) % m; }
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
#endif
}

// Modular exponentiation (base^exp % mod) using square-and-multiply
// Handles large exponents efficiently and avoids overflow via mulmod
static inline u64 modexp(u64 base, u64 exp, u64 mod)
{
    if (mod == 0) return 0;              // undefined; guard
    if (mod == 1) return 0;
    u64 result = 1 % mod;
    u64 cur = base % mod;
    while (exp > 0)
    {
        if (exp & 1ULL) result = mulmod(result, cur, mod);
        cur = mulmod(cur, cur, mod);
        exp >>= 1ULL;
    }
    return result;
}

// -------------------- Sequence generation --------------------
static void generateSequence()
{
    g_seq.clear();
    if (g_mod == 0)
    {
        std::cout << "\n\x1b[31mModulo cannot be 0.\x1b[0m\n";
        return;
    }

    std::unordered_set<u64> seen;
    u64 i = 1;

    // Generate sequence until a repeat is found
    std::cout << "\nGenerating sequence with base=" << g_base << " modulo=" << g_mod << " ...\n";
    while (true)
    {
        u64 v = modexp(g_base, i++, g_mod);
        if (seen.find(v) != seen.end()) break;
        seen.insert(v);
        g_seq.push_back(v);

        // basic safety cap to avoid runaway in odd modulus choices
        if (g_seq.size() > 5000) break;
    }

    std::cout << "\nGenerated Sequence Pattern:\n";
    for (size_t idx = 0; idx < g_seq.size(); ++idx)
    {
        std::cout << "Term " << (idx + 1) << ": " << g_seq[idx];
        if (g_showLoadingBar) displayLoadingBar((int)idx + 1, (int)g_seq.size());
        std::cout << "\n";
    }
}

// -------------------- Harmonic engine --------------------
struct Partials {
    std::vector<double> freq;    // spatial frequency
    std::vector<double> omega;   // temporal frequency
    std::vector<double> amp;     // amplitude
    std::vector<double> phase0;  // initial phase
};

// Build partials from sequence values
// Maps sequence values to partial parameters
static Partials buildPartials(const std::vector<u64>& seq, int maxPartials)
{
    // Build partials from sequence values
    Partials p;
    if (seq.empty()) return p;
    int use = (int)std::min<size_t>(seq.size(), (size_t)std::max(3, maxPartials));
    p.freq.reserve(use); p.omega.reserve(use); p.amp.reserve(use); p.phase0.reserve(use);

    // Map sequence values to partial parameters
    for (int k = 0; k < use; ++k)
    {
        u64 v = seq[k];
        int hv = (int)((v % 17ULL) + 1ULL);   // 1..17
        int tv = (int)((v % 29ULL) + 3ULL);   // 3..31
        double f  = 0.5 + 0.12 * hv;
        double w  = 0.6 + 0.07 * tv;
        double a  = 1.0 / (1.0 + k * 0.8);
        double ph = (double)((v % 360ULL)) * M_PI / 180.0;

        // Store
        p.freq.push_back(f);
        p.omega.push_back(w);
        p.amp.push_back(a);
        p.phase0.push_back(ph);
    }
    return p;
}

// -------------------- Animation view modes --------------------
// RAMP: 69 levels of "brightness" from ' ' to '@'
static const char* RAMP = " .'`^,:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
static constexpr int RAMP_LEN = 69;

// Map value in [-1,1] to RAMP character
static inline char shade(double v)  // v in [-1,1]
{
    double t = (v + 1.0) * 0.5;
    int idx = (int)std::floor(t * (RAMP_LEN - 1));
    if (idx < 0) idx = 0;
    if (idx >= RAMP_LEN) idx = RAMP_LEN - 1;
    return RAMP[idx];
}

// Draw oscilloscope view
static void drawOscilloscope(const Partials& P, int W, int H, double t)
{
    // render
    std::string buf;
    buf.reserve((size_t)W * (size_t)H + H);
    int mid = H / 2;

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            double xn = (double)x / (double)(W - 1);
            double ysum = 0.0;
            for (size_t k = 0; k < P.freq.size(); ++k)
            {
                ysum += P.amp[k] * std::sin(2.0 * M_PI * (P.freq[k] * xn) + P.omega[k] * t + P.phase0[k]);
            }
            ysum = std::tanh(ysum);
            int row = mid - (int)std::lround( ysum * (H * 0.4) );

            if (row == y && (x % 2 == 0)) buf.push_back('#');
            else if (y == mid)            buf.push_back('-');
            else                          buf.push_back(' ');
        }
        buf.push_back('\n');
    }

    buf += "Mode: Oscilloscope  |  size " + std::to_string(W) + "x" + std::to_string(H)
        + "  |  partials: " + std::to_string((int)P.freq.size())
        + "  |  Press [4] in menu to stop.\n";

    ansi_clear();
    std::cout << buf;
    std::cout.flush();
}

// Draw Lissajous view
static void drawLissajous(const Partials& P, int W, int H, double t)
{
    std::string grid;
    grid.assign((size_t)W * (size_t)H, ' ');

    int points = std::max(W, H) * 3;
    for (int i = 0; i < points; ++i)
    {
        double s = (double)i / (double)points;
        double X = 0.0, Y = 0.0;
        for (size_t k = 0; k < P.freq.size(); ++k)
        {
            double a = P.amp[k];
            X += a * std::sin(2.0 * M_PI * (P.freq[k] * s) + 0.9 * P.omega[k] * t + P.phase0[k]);
            Y += a * std::sin(2.0 * M_PI * (0.7 * P.freq[k] * s) + 1.1 * P.omega[k] * t + P.phase0[k] * 1.3);
        }
        X = std::tanh(X);
        Y = std::tanh(Y);
        int cx = (int)std::lround( (X * 0.45 + 0.5) * (W - 1) );
        int cy = (int)std::lround( (-Y * 0.45 + 0.5) * (H - 2) );
        if (cx >= 0 && cx < W && cy >= 0 && cy < H)
            grid[(size_t)cy * (size_t)W + (size_t)cx] = '*';
    }

    // render
    std::string out;
    out.reserve((size_t)W * (size_t)H + H);
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x) out.push_back(grid[(size_t)y * (size_t)W + (size_t)x]);
        out.push_back('\n');
    }
    out += "Mode: Lissajous  |  size " + std::to_string(W) + "x" + std::to_string(H)
        + "  |  partials: " + std::to_string((int)P.freq.size())
        + "  |  Press [4] in menu to stop.\n";

    ansi_clear();
    std::cout << out;
    std::cout.flush();
}

// Draw Plasma view
static void drawPlasma(const Partials& P, int W, int H, double t)
{
    std::string out;
    out.reserve((size_t)W * (size_t)H + H);

    for (int y = 0; y < H; ++y)
    {
        double yn = (double)y / (double)(H - 1);
        for (int x = 0; x < W; ++x)
        {
            double xn = (double)x / (double)(W - 1);
            double v = 0.0;
            for (size_t k = 0; k < P.freq.size(); ++k)
            {
                double sx = std::sin(2.0 * M_PI * (P.freq[k] * xn) + 0.8 * P.omega[k] * t + P.phase0[k]);
                double sy = std::cos(2.0 * M_PI * (0.6 * P.freq[k] * yn) + 1.1 * P.omega[k] * t + 0.5 * P.phase0[k]);
                v += P.amp[k] * (sx + sy);
            }
            v = std::tanh(v * 0.8);
            out.push_back(shade(v));
        }
        out.push_back('\n');
    }

    out += "Mode: Plasma  |  size " + std::to_string(W) + "x" + std::to_string(H)
        + "  |  partials: " + std::to_string((int)P.freq.size())
        + "  |  Press [4] in menu to stop.\n";

    ansi_clear();
    std::cout << out;
    std::cout.flush();
}

// -------------------- Animation runner --------------------
static void runHarmonicVisual()
{
    if (g_seq.empty())
    {
        std::cout << "\nNo sequence yet—generating with base=" << g_base
                  << " modulo=" << g_mod << "...\n";
        generateSequence();
    }
    Partials P = buildPartials(g_seq, 24);

    g_visualRunning = true;
    ansi_hide_cursor(true);
    auto t0 = std::chrono::steady_clock::now();

    while (g_visualRunning)
    {
        double t = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        switch (g_mode)
        {
            case Mode::Oscilloscope: drawOscilloscope(P, g_canvasW, g_canvasH, t); break;
            case Mode::Lissajous:    drawLissajous(P,    g_canvasW, g_canvasH, t); break;
            case Mode::Plasma:       drawPlasma(P,       g_canvasW, g_canvasH, t); break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(g_animMs));
    }

    ansi_hide_cursor(false);
    std::cout << "\n\x1b[31mAnimation stopped.\x1b[0m\n";
}

// -------------------- Menus --------------------
static void showSequence()
{
    if (g_seq.empty())
    {
        std::cout << "\nNo sequence generated yet. Set base/modulo first.\n";
        return;
    }
    std::cout << "\nCurrent Sequence:\n";
    for (size_t i = 0; i < g_seq.size(); ++i)
    {
        std::cout << "Term " << (i+1) << ": " << g_seq[i];
        if (g_showLoadingBar) displayLoadingBar((int)i + 1, (int)g_seq.size());
        std::cout << "\n";
    }
}

static void settingsMenu()
{
    while (true)
    {
        std::cout << "\n\n--- Settings ---\n";
        std::cout << "1. Animation speed (ms)          [current: " << g_animMs << "]\n";
        std::cout << "2. Canvas size (W H)             [current: " << g_canvasW << " " << g_canvasH << "]\n";
        std::cout << "3. Mode (1=Osc, 2=Lis, 3=Plasma) [current: " << (int)g_mode << "]\n";
        std::cout << "4. Back\n";
        std::cout << "Select: ";

        // input validation
        int c; if (!(std::cin >> c)) { std::cin.clear(); std::cin.ignore(1<<20, '\n'); continue; }

        if (c == 1)
        {
            std::cout << "Enter ms (10..200): ";
            int v; if (std::cin >> v && v >= 10 && v <= 200) g_animMs = v; else std::cout << "Invalid.\n";
        }
        else if (c == 2)
        {
            std::cout << "Enter W H (min 40x16): ";
            int w,h; if (std::cin >> w >> h && w>=40 && h>=16) { g_canvasW=w; g_canvasH=h; }
            else std::cout << "Invalid.\n";
        }
        else if (c == 3)
        {
            std::cout << "Mode (1=Oscilloscope, 2=Lissajous, 3=Plasma): ";
            int m; if (std::cin >> m && (m>=1 && m<=3)) g_mode = (Mode)m; else std::cout << "Invalid.\n";
        }
        else if (c == 4) return;
        else std::cout << "Invalid.\n";
    }
}

// -------------------- Main --------------------
int main()
{
    enableVT();
    std::cout << "\nInitializing with base=" << g_base << " modulo=" << g_mod << " ...\n";
    generateSequence();

    while (g_running)
    {
        std::cout << "\n--- Control Menu ---\n";
        std::cout << "1. Set base (current: " << g_base << ")\n";
        std::cout << "2. Set modulo (current: " << g_mod << ")\n";
        std::cout << "3. Show sequence\n";
        std::cout << "4. Start/Stop visual\n";
        std::cout << "5. Toggle sequence report (current: " << (g_showLoadingBar ? "ON" : "OFF") << ")\n";
        std::cout << "6. Settings\n";
        std::cout << "7. Exit\n";
        std::cout << "Select: ";
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\x1b[31mInvalid input. Enter a number.\x1b[0m\n";
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                std::string b;
                std::cout << "Enter new base (u64): ";
                if (std::cin >> b)
                {
                    try {
                        unsigned long long v = std::stoull(b);
                        g_base = v;
                        std::cout << "Base updated -> " << g_base << "\n";
                        generateSequence();
                    } catch (...) { std::cout << "\x1b[31mInvalid base.\x1b[0m\n"; }
                }
            } break;

            case 2:
            {
                std::string m;
                std::cout << "Enter new modulo (u64, >0): ";
                if (std::cin >> m)
                {
                    try {
                        unsigned long long v = std::stoull(m);
                        if (v == 0ULL) { std::cout << "\x1b[31mModulo must be > 0.\x1b[0m\n"; break; }
                        g_mod = v;
                        std::cout << "Modulo updated -> " << g_mod << "\n";
                        generateSequence();
                    } catch (...) { std::cout << "\x1b[31mInvalid modulo.\x1b[0m\n"; }
                }
            } break;

            case 3:
                showSequence();
                break;

            case 4:
                if (!g_visualRunning)
                {
                    std::cout << "Starting harmonic visual...\n";
                    std::thread([]{ runHarmonicVisual(); }).detach();
                }
                else
                {
                    g_visualRunning = false;
                }
                break;

            case 5:
                g_showLoadingBar = !g_showLoadingBar;
                std::cout << "Sequence report " << (g_showLoadingBar ? "enabled" : "disabled") << ".\n";
                break;

            case 6:
                settingsMenu();
                break;

            case 7:
                g_running = false;
                g_visualRunning = false;
                break;

            default:
                std::cout << "\x1b[31mInvalid option.\x1b[0m\n";
        }
    }

    std::cout << "\n\x1b[31mProgram terminated.\x1b[0m\n";
    return 0;
}