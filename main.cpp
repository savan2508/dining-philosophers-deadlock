/*
    Dining Philosophers Problem

    Problem Description:
    --------------------
    The Dining Philosophers problem is a classic example of a synchronization problem as per book.
    There are five philosophers sitting at a table, each alternating between thinking and eating.
    To eat, a philosopher needs two chopsticks: one on their left and one on their right.
    The philosophers share chopsticks with their neighboring philosophers. The challenge is to
    develop a solution where the philosophers do not run into a deadlock (where everyone is waiting
    for a chopstick) and avoid starvation (where a philosopher never gets to eat).

    Solution Philosophy:
    --------------------
    - Deadlock: If all philosophers pick up the chopstick on their left at the same time,
      they'll all wait indefinitely for the chopstick on their right, leading to deadlock.
    - Starvation: Even with a deadlock-free solution, a philosopher might starve if they
      never get access to both chopsticks.

    Solution Strategy:
    ------------------
    The solution is influenced by the book "Operating System Concepts" by Silberschatz, Galvin, and Gagne section 7.1.
    The solution uses semaphores to represent chopsticks and follows an asymmetric approach:
    - Odd-numbered philosophers pick up their left chopstick first, while even-numbered philosophers
      pick up their right chopstick first.
    This prevents deadlock by ensuring that not all philosophers are waiting for chopsticks in a circular pattern.
    The solution guarantees that no two adjacent philosophers eat simultaneously and avoids deadlock.

    Author: Savan Patel
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <chrono>
#include <iomanip>
#include <ctime>

constexpr int NUM_PHILOSOPHERS = 5;  // Total number of philosophers

// Binary semaphores to represent the chopsticks, initialized to 1 (available)
std::binary_semaphore chopsticks[NUM_PHILOSOPHERS] = {
    std::binary_semaphore(1),
    std::binary_semaphore(1),
    std::binary_semaphore(1),
    std::binary_semaphore(1),
    std::binary_semaphore(1)
};

// ANSI color codes for console output
#define RESET   "\033[0m"

// Activity-based colors (will combine with philosopher-specific colors)
#define THINKING "\033[32m"      // Green for thinking
#define EATING   "\033[31m"      // Red for eating
#define PICKING  "\033[33m"      // Yellow for picking up chopsticks
#define PUTTING  "\033[34m"      // Blue for putting down chopsticks

// ANSI color codes for philosopher-specific colors
#define PHIL0   "\033[35m"      // Philosopher 0 - Magenta
#define PHIL1   "\033[36m"      // Philosopher 1 - Cyan
#define PHIL2   "\033[93m"      // Philosopher 2 - Bright Yellow
#define PHIL3   "\033[95m"      // Philosopher 3 - Bright Magenta
#define PHIL4   "\033[96m"      // Philosopher 4 - Bright Cyan

/*
    Function: logWithTimestamp
    --------------------------
    Logs a message to the console with the current timestamp.
*/
void logWithTimestamp(const std::string& philosopherColor, const std::string& activityColor, const std::string& philosopherID, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "[" << std::put_time(std::localtime(&now_time), "%T") << "] "
              << philosopherColor << philosopherID << RESET
              << activityColor << message << RESET << std::endl;
}


/*
    Function: think
    ----------------
    Simulates the thinking process of a philosopher.

    Parameters:
    - philosopherID: the ID of the philosopher.

    This function simulates the philosopher thinking for a period of time.
*/
void think(const int philosopherID, const std::string& philosopherColor) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Log the philosopher's name in their specific color and the activity in the activity color
    logWithTimestamp(philosopherColor, THINKING, "Philosopher " + std::to_string(philosopherID), " is thinking.");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));  // Simulate thinking time

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Log the completion of the thinking process with the duration
    logWithTimestamp(philosopherColor, THINKING, "Philosopher " + std::to_string(philosopherID), " thought for " + std::to_string(duration) + " ms.");
}

/*
    Function: eat
    --------------
    Simulates the eating process of a philosopher.

    Parameters:
    - philosopherID: the ID of the philosopher.

    This function simulates the philosopher eating for a period of time.
*/
void eat(const int philosopherID, const std::string& philosopherColor) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Log the philosopher's name in their specific color and the activity in the activity color (eating)
    logWithTimestamp(philosopherColor, EATING, "Philosopher " + std::to_string(philosopherID), " is eating.");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));  // Simulate eating time

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Log the completion of the eating process with the duration
    logWithTimestamp(philosopherColor, EATING, "Philosopher " + std::to_string(philosopherID), " ate for " + std::to_string(duration) + " ms.");
}


/*
    Function: philosopher
    ---------------------
    Controls the actions of each philosopher: alternating between thinking and eating.

    Parameters:
    - philosopherID: the ID of the philosopher.

    Each philosopher tries to pick up their chopsticks (represented as semaphores).
    Odd philosophers pick up their left chopstick first, and even philosophers pick
    up their right chopstick first to avoid deadlock.
*/
[[noreturn]] void philosopher(const int philosopherID, const std::string& philosopherColor) {
    const int leftChopstick = philosopherID;  // Left chopstick for the philosopher
    const int rightChopstick = (philosopherID + 1) % NUM_PHILOSOPHERS;  // Right chopstick for the philosopher

    // Continuous loop for alternating between thinking and eating
    while (true) {
        think(philosopherID, philosopherColor);  // Simulate thinking process

        // Philosopher is hungry and trying to pick up chopsticks
        logWithTimestamp(philosopherColor, "", "Philosopher " + std::to_string(philosopherID), " is hungry and trying to pick up chopsticks.");

        // Asymmetric chopstick picking to prevent deadlock
        if (philosopherID % 2 == 0) {
            // Even-numbered philosophers pick up the right chopstick first
            chopsticks[rightChopstick].acquire();
            logWithTimestamp(philosopherColor, PICKING, "Philosopher " + std::to_string(philosopherID), " picked up right chopstick " + std::to_string(rightChopstick) + ".");

            chopsticks[leftChopstick].acquire();
            logWithTimestamp(philosopherColor, PICKING, "Philosopher " + std::to_string(philosopherID), " picked up left chopstick " + std::to_string(leftChopstick) + ".");
        } else {
            // Odd-numbered philosophers pick up the left chopstick first
            chopsticks[leftChopstick].acquire();
            logWithTimestamp(philosopherColor, PICKING, "Philosopher " + std::to_string(philosopherID), " picked up left chopstick " + std::to_string(leftChopstick) + ".");

            chopsticks[rightChopstick].acquire();
            logWithTimestamp(philosopherColor, PICKING, "Philosopher " + std::to_string(philosopherID), " picked up right chopstick " + std::to_string(rightChopstick) + ".");
        }

        eat(philosopherID, philosopherColor);  // Simulate eating process

        // Philosopher puts down both chopsticks after eating
        chopsticks[leftChopstick].release();
        chopsticks[rightChopstick].release();

        logWithTimestamp(philosopherColor, PUTTING, "Philosopher " + std::to_string(philosopherID), " put down chopsticks.");
    }
}


/*
    Function: main
    --------------
    Entry point of the program.

    This function creates philosopher threads and simulates the dining philosophers problem.
    Each philosopher operates concurrently.
*/
int main() {
    // Array of philosopher threads
    std::thread philosophers[NUM_PHILOSOPHERS];

    // Philosopher-specific colors
    const std::string philosopherColors[NUM_PHILOSOPHERS] = {PHIL0, PHIL1, PHIL2, PHIL3, PHIL4};

    // Create and launch philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i] = std::thread(philosopher, i, philosopherColors[i]);  // Each thread simulates a philosopher
    }

    // Join philosopher threads (this will not happen in this infinite loop simulation)
    for (auto & philosopher : philosophers) {
        philosopher.join();
    }

    return 0;  // Program never reaches here because of the infinite loop in philosopher()
}
