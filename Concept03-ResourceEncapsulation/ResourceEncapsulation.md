# Concept 03 - Resource Encapsulation
* Code Example: Example2/Exemplar/
* Code NonExample: Example2/NonExample/thread.cpp

## Example Description
When running a scheduling algorithm, the Process Control Block maintiains information about a process such as its process ID, its priority, run time etc... All of this information can be nicely encapsulated into a data structure to easily modify and keep track of it. In this example the data structure used is a struct, not a class. This worked well with the program and the privacy of a class was unnecessary. Also, it is easier to get a pipe working with a struct than with a class, since a struct is nothing more than some data sandwiched together in memory. Even though the data inside the struct is public, there are specific functions that provide a controlled manner for acessing the data. All this helps encapsulate the PCB block into a single data structure that can be manipulated by the scheduling algorithm.

There is also a QueueArray class which encapsulates a data structure that allows for an array of queues and special manipulation of those queues. It turns out to be really useful when implementing a scheduling algorithm. However, the point is that the class encapsulates all the data and functions to manipulate that data into a single data structure, just like with the PCB block struct. However, here, a class is used which provides the added security of private data members that cannot be accessed using outside code.

## NonExample Description

Thread.cpp generates a very small program, and so there is not much to encapsulate. However, the two global arrays could be and probably should be encapsulated into some sort of data structure, preferably a class. This might help with some of the issues in the program. Defining functions to act on the data could help with the data inconsistency problem by having checks in place. This does not solve the problem of a lack of process Isolation, but it would help protect some of the data. Knowing that one thread can comprise the entire parent program, at least damage could be limited when using a class, in that only restricted and minimal access is allowed.