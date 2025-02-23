# Philosophers 🍽️ 

## Description
The Philosophers project is an introduction to threading and process concepts. It illustrates a classic synchronization problem through the simulation of dining philosophers, where each philosopher must alternate between eating, thinking, and sleeping while sharing resources (forks) with their neighbors.

## 🧮 Project Overview
The program simulates philosophers sitting around a table:
- Each philosopher needs two forks to eat 🍴
- Philosophers alternate between three states: eating 🍝, sleeping 😴, and thinking 🤔
- If a philosopher doesn't eat for too long, they die 💀

## 🛠️ Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/philosophers.git
cd philosophers

# Compile the program
make
```

## 💻 Usage
```bash
# Format: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
./philo 5 800 200 200 5

# Output example:
[   0 ms] Philosopher 1 has taken a fork 🍴
[   0 ms] Philosopher 1 has taken a fork 🍴
[   0 ms] Philosopher 1 is eating 🍝
[   0 ms] Philosopher 3 has taken a fork 🍴
```

### Arguments:
- `number_of_philosophers`: Number of philosophers at the table
- `time_to_die`: Time in milliseconds before a philosopher dies of starvation
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds for sleeping
- `[number_of_meals]`: Number of times each philosopher must eat (optional)

## 🎨 Status Colors
Messages are displayed with colors for better visibility:
- 🟢 Green: Eating
- 🔵 Blue: Sleeping
- 🟡 Yellow: Thinking
- 🔆 Cyan: Taking a fork
- 🔴 Red: Death

## 🔍 Implementation Details
1. **Thread Management**:
   - One thread per philosopher
   - One monitor thread for death detection
   
2. **Resource Protection**:
   - Mutex usage for forks
   - Deadlock prevention
   
3. **Precise Timing**:
   - Accurate time management with usleep
   - Constant state monitoring

## Project Structure 📁
```
📁 include/
📁 src/
│ ├── actions.c    # Status and meal counting
│ ├── init.c       # Data structures initialization
│ ├── monitor.c    # Death monitoring
│ ├── philo.c      # Main program
│ ├── routine.c    # Philosopher lifecycle
│ ├── time.c       # Time utilities
│ ├── tools.c      # Parsing and thread creation
│ └── utils.c      # Utility functions
└── Makefile
```

## 🎯 Key Points
- Precise timing management
- Data race prevention
- Resource optimization
- Clean memory management

## 🙏 Acknowledgments
- Thanks to Aristotle, Plato, and Socrates for philosophical inspiration

Happy Dining! 🍽️✨
