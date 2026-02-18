# 🍝 Philosophers

### A multithreading simulation of the Dining Philosophers Problem, implemented with POSIX threads and mutexes for safe concurrent resource sharing.

[![42 School](https://img.shields.io/badge/42-School-blue?style=for-the-badge)](https://42.fr/)
[![Language](https://img.shields.io/badge/Language-C-orange?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-passing-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)
[![Grade](https://img.shields.io/badge/Grade-125%2F100-success?style=for-the-badge)](https://github.com/Adavitas/philosophers)

---

## 📋 Table of Contents

- [About](#-about)
- [Features](#-features)
- [How It Works](#-how-it-works)
- [Installation](#-installation)
- [Usage](#-usage)
- [Simulation Rules](#-simulation-rules)
- [Project Structure](#-project-structure)
- [Synchronization Strategy](#-synchronization-strategy)
- [Error Handling](#%EF%B8%8F-error-handling)
- [Make Commands](#%EF%B8%8F-make-commands)
- [Testing Examples](#-testing-examples)
- [Author](#-author)
- [License](#-license)

---

## 🎯 About

Philosophers is a 42 School project based on the classic **Dining Philosophers Problem**, formulated by Edsger Dijkstra. The challenge explores the fundamentals of **concurrent programming** — threads, mutexes, and race conditions — by simulating philosophers sitting around a circular table, alternating between eating, thinking, and sleeping.

Each philosopher needs two forks to eat, but there are only as many forks as philosophers, requiring careful synchronization to avoid **deadlocks** and **data races** while ensuring no philosopher starves.

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png" width="300" alt="Dining Philosophers Problem"/>
</p>

---

## ✨ Features

- **POSIX Threads** — each philosopher runs as an independent thread
- **Mutex-based synchronization** — forks and shared state protected by mutexes
- **Deadlock prevention** — even/odd fork-pickup ordering eliminates circular wait
- **Precise timing** — busy-wait sleep for accurate millisecond timestamps
- **Death detection** — dedicated monitor thread detects starvation in real-time
- **Meal counting** — optional stop condition when all philosophers eat enough
- **Single philosopher handling** — graceful edge case for one philosopher
- **Data race free** — all shared data access is mutex-protected
- **Memory leak free** — proper cleanup of all allocated resources

---

## 🧠 How It Works

The simulation follows a strict lifecycle for each philosopher:

```
┌──────────┐     ┌──────────┐     ┌──────────┐
│ THINKING │ ──► │  EATING  │ ──► │ SLEEPING │ ──┐
└──────────┘     └──────────┘     └──────────┘   │
     ▲                                            │
     └────────────────────────────────────────────┘
```

1. **Think** — philosopher waits for forks to become available
2. **Eat** — picks up two forks, eats for `time_to_eat` ms, puts forks down
3. **Sleep** — sleeps for `time_to_sleep` ms
4. **Repeat** — until death or all philosophers have eaten enough

A separate **monitor thread** continuously checks whether any philosopher has starved (exceeded `time_to_die` since last meal) or if all philosophers completed their required meals.

---

## 🔧 Installation

```bash
# Clone the repository
git clone https://github.com/Adavitas/philosophers.git
cd philosophers

# Compile the project
make
```

### Compilation Flags

The project is compiled with: `-Wall -Wextra -Werror -pthread`

---

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table (max 200) |
| `time_to_die` | Time in ms a philosopher can go without eating before dying |
| `time_to_eat` | Time in ms it takes for a philosopher to eat |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops when all philosophers have eaten this many times |

### Example Output

```bash
$ ./philo 5 800 200 200
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
0 5 is thinking
200 1 is sleeping
200 3 has taken a fork
200 3 has taken a fork
200 3 is eating
200 2 is sleeping
...
```

Each log line follows the format: `timestamp_in_ms philosopher_id action`

---

## 🎮 Simulation Rules

| Rule | Description |
|------|-------------|
| 🪑 Seating | Philosophers sit in a circle, forks placed between each pair |
| 🍴 Forks | A philosopher needs both left and right forks to eat |
| 🍝 Eating | After eating, forks are placed back on the table |
| 💤 Sleeping | After eating, the philosopher sleeps |
| 💭 Thinking | After sleeping, the philosopher thinks |
| 💀 Death | If a philosopher doesn't start eating within `time_to_die` ms, they die |
| 🛑 Stop | Simulation stops when a philosopher dies or all have eaten enough |

---

## 📂 Project Structure

```
philosophers/
├── 📄 Makefile                  # Build configuration
├── 📂 includes/                 # Header files
│   └── philo.h                # Main header with structs & prototypes
└── 📂 src/                      # Source files
    ├── philosophers.c         # Entry point & main function
    ├── parsing.c              # Input validation & ft_atoi
    ├── setup.c                # Table & philosopher initialization
    ├── threads.c              # Thread creation, joining & cleanup
    ├── actions.c              # Eat, sleep, think & lifecycle
    ├── monitor.c              # Death detection & meal counting
    ├── output.c               # Thread-safe logging & sim_ended check
    └── time.c                 # Precise time & sleep utilities
```

---

## 🔒 Synchronization Strategy

### Fork Ordering (Deadlock Prevention)
- **Even-numbered** philosophers pick up the **right** fork first
- **Odd-numbered** philosophers pick up the **left** fork first
- This breaks the circular wait condition, preventing deadlocks

### Mutexes Used

| Mutex | Purpose |
|-------|---------|
| `forks[i]` | One mutex per fork — prevents two philosophers from using the same fork |
| `mtx_print` | Protects `printf` — ensures log messages don't interleave |
| `mtx_stop` | Guards `sim_stop` flag — safe read/write of simulation state |
| `mtx_meal` | Per-philosopher — protects `last_eat` and `eat_count` from races |

### Think Time Balancing (Odd Philosophers)
For an odd number of philosophers, a calculated think time is added to prevent starvation by ensuring fair fork access across the cycle.

---

## ⚠️ Error Handling

The program handles various error cases:

- Wrong number of arguments
- Non-numeric or negative input values
- Integer overflow protection
- Number of philosophers exceeding maximum (200)
- Invalid optional meal count

Error output is printed to stdout with descriptive messages:
```
Usage: ./philo 5 800 200 200 [meals]
Error: invalid number_of_philosophers
Error: invalid time_to_die
```

---

## 🛠️ Make Commands

```bash
make          # Compile the philo program
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything
```

---

## 🧪 Testing Examples

```bash
# Basic test — 5 philosophers, should run indefinitely without dying
./philo 5 800 200 200

# Philosopher should die
./philo 4 310 200 100

# No philosopher should die (tight timing)
./philo 5 800 200 200

# Stop after each philosopher eats 7 times
./philo 5 800 200 200 7

# Single philosopher — should die after time_to_die
./philo 1 800 200 200

# Edge case — philosopher dies immediately with very short time_to_die
./philo 4 200 205 200

# Stress test — many philosophers
./philo 200 800 200 200
```

### Validation Tips

```bash
# Check for data races with Thread Sanitizer
cc -Wall -Wextra -Werror -pthread -fsanitize=thread -g src/*.c -I includes -o philo_tsan
./philo_tsan 5 800 200 200

# Check for memory leaks with Valgrind (disable for thread sanitizer)
valgrind --tool=helgrind ./philo 5 800 200 200 7
```

---

## 👨‍💻 Author

**Aleksandre Davitashvili** (Adavitas) — 42 Student

[![GitHub](https://img.shields.io/badge/GitHub-Adavitas-181717?style=for-the-badge&logo=github)](https://github.com/Adavitas)

---

## 📝 License

This project is part of the 42 School curriculum.

This project was created as part of the 42 School common core curriculum.
