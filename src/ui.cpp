#include "ui.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>

#include "ex1.h"
#include "ex2.h"
#include "ex3.h"
#include "ex4.h"
#include "ex5.h"
#include "ex6.h"
#include "ex7.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#endif

UI &UI::getInstance() {
    static UI instance;
    return instance;
}

UI::UI() {
}

UI::~UI() {
}

void UI::start() {
    // Database is already loaded by the Database singleton constructor
    // No need to load it again here

    while (true) {
        clearScreen();
        std::cout << "=== Homework ===" << std::endl << std::endl;
        std::cout << "1. Sum of 1 to N" << std::endl;
        std::cout << "2. Character case switch" << std::endl;
        std::cout << "3. Factorial sum" << std::endl;
        std::cout << "4. Odd-Even balanced number" << std::endl;
        std::cout << "5. Lucky number" << std::endl;
        std::cout << "6. Prime between a and b list" << std::endl;
        std::cout << "7. Prime factorization of n list" << std::endl;
        std::cout << "0. Exit" << std::endl << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                Ex1 ex1;
                UI *ui1 = &ex1;
                ui1->start_loop();
                break;
            }
            case 2: {
                Ex2 ex2;
                UI *ui2 = &ex2;
                ui2->start_loop();
                break;
            }
            case 3: {
                Ex3 ex3;
                UI *ui3 = &ex3;
                ui3->start_loop();
                break;
            }
            case 4: {
                Ex4 ex4;
                UI *ui4 = &ex4;
                ui4->start_loop();
                break;
            }
            case 5: {
                Ex5 ex5;
                UI *ui5 = &ex5;
                ui5->start_loop();
                break;
            }
            case 6: {
                Ex6 ex6;
                UI *ui6 = &ex6;
                ui6->start_loop();
                break;
            }
            case 7: {
                Ex7 ex7;
                UI *ui7 = &ex7;;
                ui7->start_loop();
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                waitForEnter();
        }
    }
}

void UI::start_loop() {
    char choice;
    while (choice != 'q' && choice != 'Q') {
        clearScreen();
        this->process();
        std::cout << "Press q to quit, or other key to continue.\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string UI::getPasswordInput(const std::string &prompt) {
    std::string password;
    std::cout << prompt;

#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r') {
        // Read until Enter key
        if (ch == '\b') {
            // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            password += ch;
            std::cout << '*'; // Print asterisk instead of the character
        }
    }
    std::cout << std::endl;
#else
    // Save terminal settings
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;  // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read password
    std::getline(std::cin, password);

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    return password;
}

void UI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UI::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string UI::getInput(const std::string &prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int UI::getQuantityInput(const std::string &prompt) {
    double amount;
    while (true) {
        std::cout << prompt;
        if (std::cin >> amount && amount > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return amount;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid amount. Please try again.\n";
    }
}

double UI::getAmountInput(const std::string &prompt) {
    double amount;
    while (true) {
        std::cout << prompt;
        if (std::cin >> amount && amount > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return amount;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid amount. Please try again.\n";
    }
}

std::chrono::system_clock::time_point UI::getDateInput(const std::string &prompt) {
    while (true) {
        std::string dateStr = getInput(prompt);
        std::tm tm = {};
        std::stringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");

        if (!ss.fail()) {
            return std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
        std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
    }
}
