#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <cmath>

// Global atomic variables to allow for thread-safe user input adjustments
std::atomic<int> base(2);        // Base for the sequence (default: 2)
std::atomic<int> modulo(9);      // Modulo value (default: 9)
std::atomic<bool> running(true); // Controls program execution
std::atomic<int> power(1);       // Power to be reset when new input is given

// Function to generate and display the modular harmonic sequence
void displayHarmonics()
{
    int power = 1; // Start with 2^1 (or base^1)

    while (running)
    {
        int result = static_cast<int>(pow(base.load(), power)) % modulo.load();

        // Display the current term in the harmonic sequence
        std::cout << "Term " << power << ": " << result << std::endl;

        // Increment power for next term in sequence
        power++;

        // Delay for readability, allowing the user time to see changes in real time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// Function to handle user input and dynamically adjust sequence parameters
void handleUserInput()
{
    while (running)
    {
        std::cout << "\n--- Control Menu ---" << std::endl;
        std::cout << "1. Set new base (current: " << base << ")" << std::endl;
        std::cout << "2. Set new modulo (current: " << modulo << ")" << std::endl;
        std::cout << "3. Exit program" << std::endl;
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int newBase;
            std::cout << "Enter new base: ";
            std::cin >> newBase;
            base = newBase;
            std::cout << "Base updated to " << base.load() << std::endl;
            break;
        }
        case 2:
        {
            int newModulo;
            std::cout << "Enter new modulo: ";
            std::cin >> newModulo;
            modulo = newModulo;
            std::cout << "Modulo updated to " << modulo.load() << std::endl;
            break;
        }
        case 3:
            running = false; // Signal to end program
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}

int main()
{
    std::cout << "Starting harmonic sequence display...\n";

    // Start sequence display in a separate thread for non-blocking operation
    std::thread displayThread(displayHarmonics);

    // Run user input handling on the main thread
    handleUserInput();

    // Wait for display thread to finish before closing the program
    displayThread.join();

    std::cout << "Program terminated." << std::endl;
    return 0;
}
