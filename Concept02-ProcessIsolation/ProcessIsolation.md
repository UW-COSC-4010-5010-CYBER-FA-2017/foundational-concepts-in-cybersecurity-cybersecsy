# Concept 02 - ProcessIsolation

## Example Description
Process Isolation requires that memory spaces for processes be kept separate. 
In this example, We have 3 processes: commander, processManager, and reporter. 
The commander will fork and exec the processManager which will fork and exec 
the reporter. Each process has isolated memory space due to how fork 
duplicates processes. All the memory spaces are copied into separate, newly 
allocated, memory. The parent and child maintain separate memory spaces. This 
is important because when the processManager forks and its child executes the 
reporter, the system overwrites the child's memory with that of the reporter. 
The same thing occurs when the Commander forks and execs the processManager. 
If that memory were shared to begin with, it might allow for an exploit into 
a child program.

## NonExample Description
In this example, there is one process that creates 10 threads, all of which 
share the same memory space. Not only that, they share the same space as the 
parent thread. This allows any of the threads to modify data that another is 
looking at or using. In fact, the output demonstrates what can happen when 
multiple processes share the same memory space, as is the case with threads. 
Data intregrity is compleletly lost and the behavior of the program is 
undefined. Mutexes or semaphores can be used to help with data and thread 
syncronization. However, that does not remove the attack vector introduced by 
the shared memory. If one thread were to be compromised, the main program could 
be compromised as well, leading to any number of security risks.

----
![Isolation](/Concept02-ProcessIsolation/Isolation.gif)
----
