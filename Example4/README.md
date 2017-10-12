Example 4: Abstraction(7), Simplicity(9), and Minimization(10) 


This example consists of threefiles, DisjointSet.hpp and driver.cpp. DisjointSet.h implements a disjoint set data structure via a templated class. It performs the normal functions of a disjoint set including insert, merge, and find. There is also a print function to facilitate easy viewing of the objects contents. 

This exemplifies abstraction mainly because it is a template class and a class with private data members is used. Since it is templated, any data type can be used with the class. Only knowing the behavior of the functions is necessary for a programmer to use the DisjointSet data structure. 

This exemplifies simplicity in that it has a very targeted job, to implement a disjoint set data structure. There are only a few methods that each accomplish a specific task that is described in the .hpp file. Again, the programmer need not concern himself with the how only the what.

Finally this also exemplifies minimization because it is a small targeted piece of code. Also a class is used, which helps prevent data from being accessed. Only the parts of the disjoint set that are meant to be accessed are allowed to be accessed. This minimizes the target area for an exploit in the code.

The driver just does some operations with the disjoint set data structure to show that is works.

The driver is unable to do anything but call the public methods which provide for a controlled environment on the data. Even when DisjointSet is given an invalid input to its functions, it handles it in a documented manner and does not crash.
