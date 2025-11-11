# Philosophers
Dining philosophers problem. Concurrent programming - multi-threading, data races and mutexes synchronization.

# Build
To build files, just type:
```Bash
make
```
# Start simulation
Start executable with arguments in specific order:
- number of philosopers,
- time to die [ms]
- time to eat [ms]
- time to sleep [ms]
- number of times each philosopher must eat to finish simulation [optional argument - without it simulation should go on until you specifically break it by CTRL+C]
For example:
```Bash
./philo 6 800 200 200 5
```
6 philosopers will swap forks to eat for 200ms, sleep for 200ms and do it 5 times alltogether. The time to die is 800ms so it should be safe for everyone to eat, sleep and be idle while other are using forks.

# Shuffle the values
You can change the arguments values, but **remember** - the lower time to die is and higher time to eat or sleep, the bigger chances some philosoper **will not survive**.
Moreover, If the number of philosophers is an odd number and the time to die is too short or sleeping/eating time to high, the higher chances that one of philosopers will start starving and die. Using even numbers, they will swap forks swiftly.

# Fun fact
Number of philosophers equals number of forks. Forks' number needed to eat is 2. If you set the philo number to 1, there is only 1 fork, meaning that philosopher will die after 800ms - or the time you set yourself. (no competition though not enough forks to eat).

# Beauty of multithreading
Set some safe values and feel the infinite rush in terminal log. See how your processor using context switching to feed all the threads. All in one process.


