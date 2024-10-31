#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

// Global atomic variables to allow for thread-safe user input adjustments
std::atomic<int> base(2);        // Base for the sequence (default: 2)
std::atomic<int> modulo(9);      // Modulo value (default: 9)
std::atomic<bool> running(true); // Controls program execution
std::atomic<int> power(1);       // Power to be reset when new input is given

std::mutex inputMutex; // Mutex to prevent simulataneous access to input/output stream

// Modular exponentiation for efficiency
int modularExponentiation(int base, int exponent, int mod)
{
    int result = 1;
    base = base % mod;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        { // If exponent is odd
            result = (result * base) % mod;
        }
        exponent = exponent >> 1; // Divide exponent by 2
        base = (base * base) % mod;
    }
    return result;
}

// Function to generate and display the modular harmonic sequence
void displayHarmonics()
{
    while (running)
    {
        // Lock the input mutex to prevent overlapping output
        std::lock_guard<std::mutex> lock(inputMutex);

        int currentPower = power.load();
        int result = modularExponentiation(base.load(), currentPower, modulo.load());

        // Display the current term in the harmonic sequence
        std::cout << "Term " << currentPower << ": " << result << std::endl;

        // Increment power for next term in sequence
        power = currentPower + 1;

        // Delay for readability, allowing the user time to see changes in real time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// Function to handle user input and dynamically adjust sequence parameters
void handleUserInput()
{
    while (running)
    {
        std::cout << "\n--- Control Menu ---\n";
        std::cout << "1. Set new base (current: " << base << ")\n";
        std::cout << "2. Set new modulo (current: " << modulo << ")\n";
        std::cout << "3. Exit program\n";
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
            power = 1; // Reset power to restart the sequence
            std::cout << "Base updated to " << base.load() << "\n";
            break;
        }
        case 2:
        {
            int newModulo;
            std::cout << "Enter new modulo: ";
            std::cin >> newModulo;
            modulo = newModulo;
            power = 1; // Reset power to restart the sequence
            std::cout << "Modulo updated to " << modulo.load() << "\n";
            break;
        }
        case 3:
            running = false; // Signal to end program
            std::cout << "Exiting program..." << "\n";
            break;
        default:
            std::cout << "Invalid option. Please try again." << "\n";
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

    std::cout << "Program terminated." << "\n";
    return 0;
}
