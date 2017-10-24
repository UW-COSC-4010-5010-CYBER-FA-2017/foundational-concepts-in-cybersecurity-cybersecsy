# Concept 02 - Process Isolation
* Code Example: Example2/Exemplar/
* Code NonExample: Example2/NonExample/thread.cpp

----
![Isolation](/Concept02-ProcessIsolation/Isolation.gif)
----

## Example Description
Process Isolation requires that memory spaces for processes be kept seperate. In this example, We have 3 processes, commander, processManager, and reporter. Commander will fork and exec the processManager which will fork and exec the reporter. The processes memory spaces are kept isolated because of the way that fork duplicates processes. All the memory space is copied into seperate newly allocated memory. The parent and child mantain seperate memory spaces. Which is important because when exec is called it overwrites the child's memory with that of the process being executed. If that memory were shared to begin with, it might allow for an exploit into an exec'ed program which is something you might not expect.

## NonExample Description

In this example, there is one process that runs. However, this process creates 10 threads, all of which share the same memory space. Not only that, they share the space as the parent thread. At any point, one of the threads can modify data that another is looking at or using. In fact, the output demonstrates what can happen when multiple processes share the same memory space, as is the case with threads. Data intregrity is compleletly lost and the behavior of the program is undefined. This is a small program, but it demonstrates the problem with shared memory spaces. Mutexes or semaphores can be used to help with data and thread syncronization. However, that does not remove the attack vector introduced by the shared memory. For example, if one thread were to be comprimised, the main program could be comprimised as well which could lead to any number of security risks.