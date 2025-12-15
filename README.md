# Pilosophers

## 🌟 Overview

**Pilosophers** is an engaging implementation of the classic Dining Philosophers problem, a cornerstone project in the 42 School curriculum. This program simulates a group of philosophers seated around a table, sharing a limited number of forks to eat spaghetti. The challenge lies in managing concurrent access to resources (forks) using threads and mutexes, preventing deadlocks, starvation, and ensuring no philosopher dies from hunger.

Through this project, key concepts in multithreading and synchronization are demonstrated, showcasing efficient resource management in a multi-process environment. It's a perfect blend of theoretical computer science and practical coding, highlighting how to handle concurrency issues in C.

## 🚀 Features

- **Multi-Threaded Simulation**: Each philosopher runs as a separate thread, mimicking real concurrent processes.
- **Synchronization with Mutexes**: Ensures safe access to shared forks, avoiding race conditions and deadlocks.
- **Configurable Parameters**: Customize the number of philosophers, time to die, eat, sleep, and optional meal limits.
- **Real-Time Logging**: Displays timestamped actions (eating, thinking, sleeping, forking, dying) for each philosopher.
- **Death and Saturation Detection**: The simulation stops if a philosopher dies or all have eaten the required number of meals.
- **Efficient Resource Management**: Implements an algorithm to allocate and free resources dynamically for optimal performance.
- **Clean Exit Handling**: Properly joins threads and destroys mutexes upon completion.

## 🛠️ Technologies Stack

- **Language**: C, adhering to strict norms for clean, efficient code.
- **Concurrency**: POSIX Threads (pthreads) for multi-threading.
- **Synchronization**: Mutexes to manage shared resources safely.
- **Build Tool**: Makefile for easy compilation and cleaning.
- **Other**: Standard C libraries (stdio, stdlib, unistd, etc.) for I/O and timing.

This stack focuses on low-level programming to deepen understanding of operating system concepts.

## 📋 Installation Guide

### Prerequisites
- GCC compiler
- Make utility
- POSIX-compliant system (Linux or macOS recommended)

### Steps
1. **Clone the Repository**:
git clone https://github.com/ftemori/Pilosophers.git
cd Pilosophers

2. **Build the Program**:
make
- This compiles the source files into the executable `philo`.

3. **Clean Up (Optional)**:
make clean   # Remove object files
make fclean  # Remove executable and objects
make re      # Rebuild everything

## 🎮 Usage

Run the program with the following command-line arguments:
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

- **number_of_philosophers**: The number of philosophers (and forks) at the table (1-200 recommended).
- **time_to_die**: Time (ms) a philosopher can go without eating before dying.
- **time_to_eat**: Time (ms) it takes to eat a meal.
- **time_to_sleep**: Time (ms) spent sleeping after eating.
- **[optional] number_of_times_each_philosopher_must_eat**: If specified, simulation stops when all have eaten this many times.

### Examples
- Basic simulation: `./philo 5 800 200 200`
- With meal limit: `./philo 5 800 200 200 7`

Watch the console for real-time updates on each philosopher's state. The program exits gracefully upon completion or detection of a death.
