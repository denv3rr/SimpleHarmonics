#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <thread>
#include <chrono>
#include <gmpxx.h>
#include <iomanip> // For std::setw and formatting output
#include <conio.h> // For non-blocking key input in Windows

// Global Variables for Sequence and User Controls
mpz_class base = 2;
mpz_class modulo = 9;
std::vector<mpz_class> sequencePattern;
bool running = true;
bool sequenceRunning = false;
bool showLoadingBar = true;
bool animationRunning = false;
int animationSpeed = 50; // Set speed of animation (in milliseconds per update)

// Forward Declarations
void displayLoadingBar(int progress, int total);
void displayAnimation();
void handleSettingsMenu();

// Modular exponentiation function using GMP's mpz_class
mpz_class modularExponentiation(mpz_class base, mpz_class exponent, mpz_class mod)
{
    mpz_class result = 1;
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exponent.get_mpz_t(), mod.get_mpz_t());
    return result;
}

// Function to generate the sequence pattern dynamically based on current base and modulo
void generateSequencePattern()
{
    sequencePattern.clear();
    std::set<mpz_class> seen;
    mpz_class currentValue = base;
    int i = 1;

    while (true)
    {
        currentValue = modularExponentiation(base, i++, modulo);
        if (seen.count(currentValue) > 0)
            break;
        seen.insert(currentValue);
        sequencePattern.push_back(currentValue);
    }

    std::cout << "\nGenerated Sequence Pattern:\n";
    for (size_t idx = 0; idx < sequencePattern.size(); ++idx)
    {
        std::cout << "Term " << idx + 1 << ": " << sequencePattern[idx];
        if (showLoadingBar)
        {
            displayLoadingBar(idx + 1, sequencePattern.size());
        }
        std::cout << "\n";
    }
    sequenceRunning = false;
}

// Loading bar function for visual feedback
void displayLoadingBar(int progress, int total)
{
    int barWidth = 30;
    int pos = (progress * barWidth) / total;

    std::cout << " [";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "\033[32m=\033[0m";
        else if (i == pos)
            std::cout << "\033[32m>\033[0m";
        else
            std::cout << " ";
    }
    std::cout << "] " << (100 * progress) / total << "% ";
    std::cout.flush();
}

// Function to animate the wave pattern using the sequence in memory
void displayAnimation()
{
    animationRunning = true;
    int direction = 1; // Forward direction
    int index = 0;
    const int termLabelWidth = 10; // Adjust to fit longest label ("Term X:")
    const int valueWidth = 10;     // Adjust to fit largest value

    while (animationRunning)
    {
        system("CLS"); // Clear console for a clean frame

        for (size_t idx = 0; idx < sequencePattern.size(); ++idx)
        {
            std::cout << std::left << std::setw(termLabelWidth)
                      << ("Term " + std::to_string(idx + 1) + ":");
            std::cout << std::setw(valueWidth) << sequencePattern[idx];

            if (idx == index && showLoadingBar)
            {
                displayLoadingBar(idx + 1, sequencePattern.size()); // Active term shows progress
            }
            else if (showLoadingBar)
            {
                std::cout << " []"; // Empty status bar when not selected
            }

            std::cout << "\n";
        }

        // Add reminder at the bottom of the console
        std::cout << "\nPress '4' and Enter to stop the animation...\n";

        index += direction;

        // Reverse direction at boundaries
        if (index == sequencePattern.size() - 1 || index == 0)
        {
            direction = -direction;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
    }

    std::cout << "\n\n\033[31mAnimation stopped.\033[0m\n\n";
}

// Function to handle user input and control flow
void handleUserInput()
{
    while (running)
    {
        std::cout << "\n\n--- Control Menu ---\n";
        std::cout << "1. Set new base (current: " << base << ")\n";
        std::cout << "2. Set new modulo (current: " << modulo << ")\n";
        std::cout << "3. Start sequence\n";
        std::cout << "4. Start/Stop animation\n";
        std::cout << "5. Toggle loading bar (current: " << (showLoadingBar ? "ON" : "OFF") << ")\n";
        std::cout << "6. Settings\n";
        std::cout << "7. Exit program\n";
        std::cout << "Select an option: ";
        std::cout.flush();

        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[31mInvalid input. Please enter a number.\033[0m\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            std::string newBase;
            std::cout << "Enter new base: ";
            if (std::cin >> newBase)
            {
                base = mpz_class(newBase);
                std::cout << "\nBase updated to " << base << "\n";
                generateSequencePattern(); // Regenerate sequence automatically
            }
            else
            {
                std::cout << "\033[31mInvalid base input.\033[0m\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        }
        case 2:
        {
            std::string newModulo;
            std::cout << "Enter new modulo: ";
            if (std::cin >> newModulo)
            {
                modulo = mpz_class(newModulo);
                std::cout << "\nModulo updated to " << modulo << "\n";
                generateSequencePattern(); // Regenerate sequence automatically
            }
            else
            {
                std::cout << "\033[31mInvalid modulo input.\033[0m\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        }
        case 3:
            if (!sequencePattern.empty())
            {
                std::cout << "\nDisplaying current sequence:\n";
                for (size_t idx = 0; idx < sequencePattern.size(); ++idx)
                {
                    std::cout << "Term " << idx + 1 << ": " << sequencePattern[idx];
                    if (showLoadingBar)
                    {
                        displayLoadingBar(idx + 1, sequencePattern.size());
                    }
                    std::cout << "\n";
                }
            }
            else
            {
                std::cout << "\nNo sequence generated yet. Please set base and modulo.\n";
            }
            break;
        case 4:
            if (!animationRunning)
            {
                std::cout << "\nStarting animation...\n";
                std::thread animationThread(displayAnimation);
                animationThread.detach(); // Run animation independently
            }
            else
            {
                animationRunning = false; // Stop animation
            }
            break;
        case 5:
            showLoadingBar = !showLoadingBar;
            std::cout << "\nLoading bar " << (showLoadingBar ? "enabled" : "disabled") << ".\n";
            break;
        case 6:
            handleSettingsMenu();
            break;
        case 7:
            running = false;
            animationRunning = false; // Ensure animation stops
            std::cout << "\nExiting program...\n";
            return;
        default:
            std::cout << "\n\033[31mInvalid option. Please try again.\033[0m\n";
        }
    }
}

// Settings Menu
void handleSettingsMenu()
{
    while (true)
    {
        std::cout << "\n\n--- Settings Menu ---\n";
        std::cout << "1. Set animation speed (current: " << animationSpeed << "ms)\n";
        std::cout << "2. Back to main menu\n";
        std::cout << "Select an option: ";
        std::cout.flush();

        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[31mInvalid input. Please enter a number.\033[0m\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Enter new animation speed (ms): ";
            if (std::cin >> animationSpeed && animationSpeed > 0)
            {
                std::cout << "\nAnimation speed set to " << animationSpeed << "ms.\n";
            }
            else
            {
                std::cout << "\033[31mInvalid speed input. Please enter a positive integer.\033[0m\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        case 2:
            return; // Return to main menu
        default:
            std::cout << "\033[31mInvalid option. Please try again.\033[0m\n";
        }
    }
}

// Main program
int main()
{
    std::cout << "\n\nInitializing sequence with default base (" << base << ") and modulo (" << modulo << ")...\n";
    generateSequencePattern(); // Generate initial sequence at load

    handleUserInput();
    std::cout << "\n\n\033[31mProgram terminated.\033[0m\n\n\n";
    return 0;
}