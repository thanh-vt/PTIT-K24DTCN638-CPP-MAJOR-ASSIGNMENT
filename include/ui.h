#pragma once

#include <chrono>
#include <memory>

class UI {
public:
    static UI& getInstance();

    virtual void start() final;

    virtual void start_loop() final;

private:

    // Prevent copying
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;

protected:
    UI();
    ~UI();
    // Helper functions
    void clearScreen();
    void waitForEnter();
    std::string getInput(const std::string& prompt);
    std::string getPasswordInput(const std::string& prompt);
    int getQuantityInput(const std::string& prompt);
    double getAmountInput(const std::string& prompt);
    std::chrono::system_clock::time_point getDateInput(const std::string& prompt);

    virtual void process() {};
}; 