#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <vector>
#include <set>
#include <limits>
#include <gmpxx.h> // GMP C++ interface for arbitrary precision integers

// Global atomic variables for thread-safe operations
std::atomic<bool> running(true);          // Controls program execution
std::atomic<bool> sequenceRunning(false); // Controls display sequence and loading bar

mpz_class base = 2;                     // Base for the sequence (default: 2)
mpz_class modulo = 9;                   // Modulo value (default: 9)
std::vector<mpz_class> sequencePattern; // Dynamic sequence pattern based on base and modulo
std::mutex outputMutex;                 // Mutex for managing console output

// Modular exponentiation function using GMP's mpz_class
mpz_class modularExponentiation(mpz_class base, mpz_class exponent, mpz_class mod)
{
    mpz_class result = 1;
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exponent.get_mpz_t(), mod.get_mpz_t());
    return result;
}

// Function to dynamically generate the sequence pattern based on the base and modulo values
void generateSequencePattern()
{
    sequencePattern.clear();
    std::set<mpz_class> seen; // Track seen values to detect cycles
    mpz_class current = base;
    int exponent = 1;

    while (seen.find(current) == seen.end())
    {
        sequencePattern.push_back(current);
        seen.insert(current);
        current = modularExponentiation(base, ++exponent, modulo);
    }

    // Display the generated sequence pattern
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Generated sequence pattern: ";
    for (const auto &term : sequencePattern)
    {
        std::cout << term << " ";
    }
    std::cout << std::endl;
}

// Function to display the modular harmonic sequence in a looping pattern
void displayHarmonics()
{
    int patternIndex = 0;
    while (running)
    {
        if (!sequenceRunning || sequencePattern.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "\rTerm " << (patternIndex + 1) << ": " << sequencePattern[patternIndex]
                      << "                              \n";
        }

        patternIndex = (patternIndex + 1) % sequencePattern.size();  // Loop over sequence pattern
        std::this_thread::sleep_for(std::chrono::milliseconds(800)); // Slightly longer sleep for clear output
    }
}

// Loading bar function based on the sequence position
void displayLoadingBar()
{
    int barWidth = 30;
    int patternIndex = 0; // Track sequence position for the loading bar
    while (running)
    {
        if (!sequenceRunning || sequencePattern.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        int progressPercentage = (100 * patternIndex) / sequencePattern.size();
        int pos = (progressPercentage * barWidth) / 100;

        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "\rSequence state: [";
            for (int i = 0; i < barWidth; ++i)
            {
                if (i < pos)
                    std::cout << "=";
                else if (i == pos)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << progressPercentage << " %                   \r";
            std::cout.flush();
        }

        patternIndex = (patternIndex + 1) % sequencePattern.size();  // Loop through pattern
        std::this_thread::sleep_for(std::chrono::milliseconds(600)); // Reduced refresh to avoid overlap
    }
}

// Function to handle user input in a separate thread
void handleUserInput()
{
    while (running)
    {
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "\n\n--- Control Menu ---\n";
            std::cout << "1. Set new base (current: " << base << ")\n";
            std::cout << "2. Set new modulo (current: " << modulo << ")\n";
            std::cout << "3. Start sequence\n";
            std::cout << "4. Stop sequence\n";
            std::cout << "5. Exit program\n";
            std::cout << "Select an option: ";
            std::cout.flush();
        }

        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "Invalid input. Please enter a number." << std::endl;
            }
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            std::string newBase;
            std::cout << "Enter new base: ";
            std::cout.flush();
            if (std::cin >> newBase)
            {
                base = mpz_class(newBase);
                std::cout << "Base updated to " << base << std::endl;
            }
            else
            {
                std::cout << "Invalid base input. Resetting input..." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        }
        case 2:
        {
            std::string newModulo;
            std::cout << "Enter new modulo: ";
            std::cout.flush();
            if (std::cin >> newModulo)
            {
                modulo = mpz_class(newModulo);
                std::cout << "Modulo updated to " << modulo << std::endl;
            }
            else
            {
                std::cout << "Invalid modulo input. Please enter a positive integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        }
        case 3:
            generateSequencePattern(); // Update sequence pattern based on new base and modulo
            if (!sequencePattern.empty())
            {                           // Ensure the pattern is valid before starting
                sequenceRunning = true; // Start sequence and loading bar
                std::cout << "Sequence started.\n";
            }
            else
            {
                std::cout << "Error: Generated sequence pattern is empty. Check base and modulo.\n";
            }
            break;
        case 4:
            sequenceRunning = false; // Stop sequence and loading bar
            std::cout << "Sequence stopped.\n";
            break;
        case 5:
            running = false;
            sequenceRunning = false;
            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "Exiting program..." << std::endl;
            }
            return;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main()
{
    std::cout << "Starting harmonic sequence...\n";

    // Start display and loading bar threads
    std::thread displayThread(displayHarmonics);
    std::thread loadingBarThread(displayLoadingBar);
    std::thread inputThread(handleUserInput);

    // Wait for threads to finish before closing the program
    displayThread.join();
    loadingBarThread.join();
    inputThread.join();

    std::cout << "Program terminated.\n";
    return 0;
}
