#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <limits>
#include <gmpxx.h> // GMP C++ interface for arbitrary precision integers

// Global atomic variables for thread-safe operations
std::atomic<bool> running(true);    // Controls program execution
std::atomic<bool> paused(true);     // Initially pauses the display sequence and loading bar
std::atomic<int> sequenceLength(0); // Tracks the number of terms in the current sequence

mpz_class base = 2;   // Base for the sequence (default: 2)
mpz_class modulo = 9; // Modulo value (default: 9)
mpz_class power = 1;  // Power level to reset on input

std::mutex outputMutex; // Mutex for managing console output

// Modular exponentiation function using GMP's mpz_class
mpz_class modularExponentiation(mpz_class base, mpz_class exponent, mpz_class mod)
{
    mpz_class result = 1;
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exponent.get_mpz_t(), mod.get_mpz_t());
    return result;
}

// Function to generate and display the modular harmonic sequence
void displayHarmonics()
{
    while (running)
    {
        if (!paused)
        {
            mpz_class currentPower = power;
            mpz_class result = modularExponentiation(base, currentPower, modulo);

            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "Term " << currentPower << ": " << result << std::endl;
            }

            sequenceLength = static_cast<int>(currentPower.get_ui());
            power = currentPower + 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

// Loading bar function based on the sequence position
void displayLoadingBar()
{
    while (running)
    {
        if (!paused)
        {
            int progress;
            int barWidth = 30;

            progress = static_cast<int>(power.get_ui()) % sequenceLength.load();
            int pos = (progress * barWidth) / sequenceLength.load();

            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "[";
                for (int i = 0; i < barWidth; ++i)
                {
                    if (i < pos)
                        std::cout << "=";
                    else if (i == pos)
                        std::cout << ">";
                    else
                        std::cout << " ";
                }
                std::cout << "] " << int((float(progress) / sequenceLength) * 100.0) << " %\r";
                std::cout.flush();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

// Function to handle user input in a separate thread
void handleUserInput()
{
    while (running)
    {
        paused = true; // Pause sequence and loading bar

        {
            std::lock_guard<std::mutex> lock(outputMutex);
            std::cout << "\n--- Control Menu ---\n";
            std::cout << "1. Set new base (current: " << base << ")\n";
            std::cout << "2. Set new modulo (current: " << modulo << ")\n";
            std::cout << "3. Exit program\n";
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
            running = false;
            {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "Exiting program..." << std::endl;
            }
            paused = false;
            return;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }

        paused = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main()
{
    paused = true; // Start with the sequence and loading bar paused

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
