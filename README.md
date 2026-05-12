This project has been created as part of the 42 curriculum by feazeved.

This project explores the "Dining Philosophers" problem to master the complexities of concurrency, multi-threading, and inter-process communication. The goal was to manage shared resources among up to 200 concurrent philosophers without ever encountering a deadlock or resource starvation. 

Instructions
Compilation: compile from terminal commandline with "make" at directory "philo".

after the program is created, you can execute and test it with different inputs:


./philo 1 800 200 200   // with one philosopher
./philo 4 300 250 200   // with no max meal nb defined
./philo 9 500 100 200 3 // with max meal nb defined


after you are done using the program, you can clean the .o files with:
clean

to delete the execution file, type:
fclean


Resources:
- https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- https://en.wikipedia.org/wiki/Dining_philosophers_problem

AI usage:
- AI was only used for resource gathering. Especially when looking for very specific details that seems slow to find information from internet.