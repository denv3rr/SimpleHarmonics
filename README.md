# Harmonic Visualizer (C++)

A modular-exponentiation powered **visualizer** that generates repeating sequences and maps them into dynamic ASCII animations.  
No external dependencies — just C++17.

---

## Features

- **Pure C++** (no GMP required)
- **Cross-platform**: Windows, macOS, Linux
- **Three visual modes**:
  - Oscilloscope (waveform trace)
  - Lissajous (dual-axis curve)
  - Plasma (ASCII shaded field)
- Interactive menu for:
  - Base & modulo adjustment
  - Sequence inspection
  - Animation start/stop
  - Settings: animation speed, canvas size, and mode
  - Toggle progress bar

---

## Build

### Prerequisites

- g++ 7+ (C++17 capable) or MSVC 2019+
- ANSI-compatible terminal (Windows Terminal, macOS Terminal, Linux TTY)

### Compile

```bash
g++ -std=c++17 main.cpp -O2 -o harmonic
```

### Run

  - `./harmonic`
  - `.\harmonic.exe` (Windows)

### Usage

When started, the program initializes with:

  - `base = 2`
  - `modulo = 9`

## Menus

### Main

  1. Set new base
  2. Set new modulo
  3. Show sequence
  4. Start/Stop harmonic visual
  5. Toggle loading bar
  6. Settings (speed, size, mode)
  7. Exit

### Settings

  - Animation speed: set frame delay in ms (default 40)
  - Canvas size: width & height (min 40x16)
  - Mode: 1=Oscilloscope, 2=Lissajous, 3=Plasma

### Controls

  - Switch modes via Settings
  - Stop the animation from the menu with option `4`

## Notes

  - Performance: The visual runs at ~25 FPS by default.
  - Terminal size: Make sure your console window is large enough to fit the chosen canvas size.
  - Compatibility: On Windows, VT/ANSI sequences are auto-enabled.
