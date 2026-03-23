This project has been created as part of the 42 curriculum by Felipe Suassuna.

This project explores the "Dining Philosophers" problem to master the complexities of concurrency, multi-threading, and inter-process communication. The goal was to manage shared resources among up to 200 concurrent philosophers without ever encountering a deadlock or resource starvation. 

Hybrid Synchronization: Utilized mutexes for thread synchronization and semaphores for IPC to manage shared resources. 

Deadlock Prevention: Planned and implemented logic to fully eliminate circular wait conditions, ensuring high-integrity execution under maximum load. 

Verification: Used thread sanitizers to ensure 0% race conditions. 

Instructions
Compilation: Run make in the root of the mandatory or bonus directory.

Execution: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
