# Example 1 
Process Isolation(2), Modularity(5), Resource Encapsulation(3)

## Exemplar:
    make example1
Making example1 will create 3 executables, commander, processManager, and reporter. In order to run this program, you only need to execute the commander. There is an input file to do so. The basic idea of this application is to emulate a process scheduling algorithm. The input and output are really unimportant. The important thing is the way the three processes interact. Commander forks and execs processManager which will fork and exec reporter. Commander takes input commands and passes them to the processManager which does all the scheduling based on the commands it receives. In order to print the state out, processManager forks and execs reporter, which uses a pipe to send data to the reporter, which is then printed out by the reporter.

### Running the Example:
    ./commander < example1_input.txt 

**Note:** this will print a lot of stuff to stdout so I reccommend redirecting the output to a file.

prog2_input.txt consists of commands that are read in by commander, validated and sent to processManager.

## NonExample:
    make nonexample1
Making nonexample1 creates one executable, nonexample2. This is a simple program with two arrays of size 10. One is a char array and the other is an int array. 10 threads are created and the even numbered threads increment all the values in the array by 1 and vice versa for the odd numbered threads. This should result in the end arrays matching the beginning arrays. However, when you run the program, you will notice that this is not the case. In fact, every time the ending arrays are different. This is due to the shared memory space in the threads that is being accessed and modified by all of them "simulataneously". This creates a situation where data integrity is completely lost and the behavior of the program is unpredictable. Run the program a few times and you will notice this.

**Note:** If you have a fast processor that is not being used for much else, it may take a few tries to notice the data integrity issue. It is there and it is a problem. However, it sometimes is not overly apparent. Looking at the code, will show that it is indeed a problem.

### Running the NonExample:
    ./nonexample1
