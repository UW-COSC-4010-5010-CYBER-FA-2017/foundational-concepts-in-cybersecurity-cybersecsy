# Example 4: 
Abstraction(7), Simplicity(9), and Minimization(10) 


# Exemplar:
    make example4
This example consists of two files, DisjointSet.hpp and driver.cpp. DisjointSet.h. It implements a disjoint set data structure via a templated class. It performs the normal functions of a disjoint set including insert, merge, and find. There is also a print function to facilitate easy viewing of the objects contents. 

The driver just does some operations with the disjoint set data structure to show that it works.

The driver is unable to do anything but call the public methods which provide for a controlled environment on the data. Even when DisjointSet is given an invalid input to its functions, it handles it in a documented manner and does not crash.

### Running the Program:
    ./example4 

# NonExample:
    make nonexample4
There is just one file for the non example of Abstraction, Simplicity, and Minimization, driverBad.cpp. This implements the same disjoint set with the same functionality as the exemplar version. However, the methodology used to write it is completely different.

All of the code is included next to main. A global variable which is a struct is used to store the information regarding the disjoint set. The functions simply modify this global variable. Because of that, only one disjoint set can be created in the entire program unless heavy modifications are made.

The driver performs the same operations as the first driver to show that the it does the same thing. So on the surface, it appears that nothing has changed, but with a little digging this code could be exploited because there are no protections against that. It is kind of like using strcpy instead of strncpy. The first version has safeguards to make exploitation difficult. Whereas, this example does not.

### Running the Program:
    ./nonexample4 
