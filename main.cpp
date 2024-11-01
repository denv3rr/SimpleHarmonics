#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <vector>
#include <limits>
#include <gmpxx.h> // GMP C++ interface for arbitrary precision integers

// Global atomic variables for thread-safe operations
std::atomic<bool> running(true);          // Controls program execution
std::atomic<bool> sequenceRunning(false); // Controls display sequence and loading bar

mpz_class base = 2;   // Base for the sequence (default: 2)
mpz_class modulo = 9; // Modulo value (default: 9)
mpz_class power = 1;  // Power level to reset on input

std::mutex outputMutex; // Mutex for managing console output

// Example pattern sequence; modify this to use your specific sequence pattern
std::vector<mpz_class> sequencePattern = {1, 2, 4, 7, 8, 5}; // A sample predefined sequence

// Modular exponentiation function using GMP's mpz_class
mpz_class modularExponentiation(mpz_class base, mpz_class exponent, mpz_class mod)
{
    mpz_class result = 1;
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exponent.get_mpz_t(), mod.get_mpz_t());
    return result;
}

// Function to display the modular harmonic sequence and loading bar
void displayHarmonics()
{
    int patternIndex = 0;
    int patternLength = sequencePattern.size();
    while (running)
    {
        if (!sequenceRunning)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        mpz_class currentPower = power;
        mpz_class result = modularExponentiation(base, currentPower, modulo);

        {
            std::lock_guard<std::mutex> lock(outputMutex);
            // Print term
            std::cout << "Term " << currentPower << ": " << result << std::endl;

            // Calculate progress based on the position in the sequencePattern
            int progressPercentage = (patternIndex * 100) / patternLength;

            // Print loading bar
            int barWidth = 30;
            int pos = (progressPercentage * barWidth) / 100;
            std::cout << "\rSequence state:\n[";
            for (int i = 0; i < barWidth; ++i)
            {
                if (i < pos)
                    std::cout << "=";
                else if (i == pos)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << progressPercentage << " %" << std::flush;

            // Update pattern index to cycle through the sequencePattern
            patternIndex = (patternIndex + 1) % patternLength;
        }

        power = currentPower + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
                power = 1;
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
                power = 1;
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
            sequenceRunning = true; // Start sequence and loading bar
            std::cout << "Sequence started.\n";
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

    // Start display and input threads
    std::thread displayThread(displayHarmonics);
    std::thread inputThread(handleUserInput);

    // Wait for threads to finish before closing the program
    displayThread.join();
    inputThread.join();

    std::cout << "Program terminated.\n";
    return 0;
}
