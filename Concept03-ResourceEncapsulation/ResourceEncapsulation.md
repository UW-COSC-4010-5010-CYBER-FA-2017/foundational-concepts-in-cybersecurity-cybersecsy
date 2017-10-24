# Concept 03 - Resource Encapsulation
* Code Example: Example2/Exemplar/
* Code NonExample: Example2/NonExample/

## Example Description
When running a scheduling algorithm, the Process Control Block maintiains information about a process such as its process ID, its priority, run time etc... All of this information can be nicely encapsulated into a data structure to easily modify and keep track of it. In this example the data structure used is a struct, not a class. This worked well with the program and the privacy of a class was unnecessary. Also, it is easier to get a pipe working with a struct than with a class, since a struct is nothing more than some data sandwiched together in memory. Even though the data inside the struct is public, there are specific functions that provide a controlled manner for acessing the data. All this helps encapsulate the PCB block into a single data structure that can be manipulated by the scheduling algorithm.

There is also a QueueArray class which encapsulates a data structure that allows for an array of queues and special manipulation of those queues. It turns out to be really useful when implementing a scheduling algorithm. However, the point is that the class encapsulates all the data and functions to manipulate that data into a single data structure, just like with the PCB block struct. However, here, a class is used which provides the added security of private data members that cannot be accessed using outside code.

## NonExample Description
