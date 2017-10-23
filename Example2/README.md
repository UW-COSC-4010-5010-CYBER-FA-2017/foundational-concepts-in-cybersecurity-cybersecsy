# Example 2 
Process Isolation, Modularity, Resource Encapsulation

## Exemplar:
* making example2 will create 3 executables, commander, processManager, and reporter. In order to run this program, youonly need to execute the commander. There is an input file to do so. The basic idea of this application is to emulate a process scheduling algorithm. The input and output are really unimportant. The important thing is the way the three processes interact. Commander forks and execs processManager which will fork and exec reporter. Commander takes input commands and passes them to the processManager which does all the scheduling based on the commands it receives. In order to print the state out, processManager forks and execs reporter, which uses a pipe to send data to the reporter, which is then printed out.



### In order to run the program: 
    ./commander < prog2_input.txt 

**Note:** this will print a lot of stuff to stdout so I reccommend redirecting the input
to a file.

prog2_input.txt consists of commands that are read in by commander, validated and 
sent to processManager.

## NonExample

threads - non example of process isolation
forking - example fo proccess isolation
struct or just global vars - non example of encapsulation
class - example of encapsulation
sepearte .h and class files - example of modularity

scheduler - example of process isolation, modularity and encapsulation
threaded calc - non example fo those three
