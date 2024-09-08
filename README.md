# Dining Philosophers Problem

## Project Overview

This project is an implementation of the **Dining Philosophers Problem**, a classic concurrency problem in computer science. The problem illustrates the challenges of resource allocation, deadlock prevention, and starvation avoidance in concurrent systems, where philosophers alternate between thinking and eating, competing for limited resources (chopsticks).

This implementation demonstrates how to manage synchronization using semaphores and an asymmetric approach to prevent deadlock and ensure each philosopher gets to eat without starving.

## Problem Description

There are five philosophers sitting around a table. Each philosopher alternates between thinking and eating. They need two chopsticks to eat — one on their left and one on their right. Philosophers share chopsticks with their neighbors, and the challenge is to avoid **deadlock** and **starvation**:
- **Deadlock**: All philosophers grab the chopstick on their left at the same time, resulting in a situation where no philosopher can pick up both chopsticks to eat.
- **Starvation**: A philosopher may be prevented from eating indefinitely if they never get both chopsticks.

This project uses an asymmetric approach, where:
- Odd-numbered philosophers pick up their left chopstick first.
- Even-numbered philosophers pick up their right chopstick first.

## Key Features

- Each philosopher and their activities (thinking, eating, picking up chopsticks, etc.) are displayed in **color-coded output** to make the simulation more visually intuitive.
- **Semaphore-based synchronization** prevents deadlock.
- The simulation runs continuously in **parallel threads**, representing each philosopher's behavior.

## Project Structure

- **CMakeLists.txt**: Used for building the project with CMake.
- **Main source file (`main.cpp`)**: Contains the implementation of the dining philosophers problem using C++ threads and semaphores.
- **README.md**: Project overview and instructions.

## Compilation and Execution

### Prerequisites

- **C++17 or higher**: This project uses C++ standard threads and semaphores, which are supported in C++17 and beyond.
- **CMake**: Used for building the project.

### Building the Project

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/your-username/your-repository.git

2. Navigate to the project directory:
   ```bash
   cd your-repository
   
3. Create a `build` directory:
   ```bash
    mkdir build
    cd build
   
4. Run CMake to configure the project:
  ```bash
     cmake ..
  ```

5. Build the project:
    ```bash
    cmake --build .

### Running the Program
Once the project is built, you can run the executable to simulate the dining philosophers problem:
```bash
./dining_philosophers_deadlock
```

The program will continuously simulate the philosophers' behavior, displaying colored output for each philosopher and their actions (thinking, eating, picking up/putting down chopsticks).

### Output Example
The following is an example of the output from the simulation:
- Each philosopher is represented by a unique color.
- The output shows the philosopher's activity (thinking, eating) and when they pick up or put down a chopstick.
- Activities such as thinking, eating, picking up, and putting down chopsticks are displayed in different colors.
```
[12:00:01] Philosopher 0 is thinking.
[12:00:05] Philosopher 0 picked up right chopstick 1.
[12:00:06] Philosopher 0 is eating.
[12:00:07] Philosopher 0 put down right chopstick 1.
[12:00:07] Philosopher 0 is thinking.
[12:00:11] Philosopher 0 picked up right chopstick 1.
[12:00:12] Philosopher 0 is eating.
[12:00:13] Philosopher 0 put down right chopstick 1.
[12:00:13] Philosopher 0 is thinking.
```

### Customization
You can adjust the following parameters in main.cpp:
- **NUM_PHILOSOPHERS**: The number of philosophers sitting around the table.
- **sleep times for thinking and eating**: The duration for which a philosopher thinks or eats before moving to the next activity.
