Example 4: Abstraction(7), Simplicity(9), and Minimization(10) 


Exemplar:

This example consists of two files, DisjointSet.hpp and driver.cpp. DisjointSet.h implements a disjoint set data structure via a templated class. It performs the normal functions of a disjoint set including insert, merge, and find. There is also a print function to facilitate easy viewing of the objects contents. 

This exemplifies abstraction mainly because it is a template class and a class with private data members is used. Since it is templated, any data type can be used with the class. Only knowing the behavior of the functions is necessary for a programmer to use the DisjointSet data structure. 

This exemplifies simplicity in that it has a very targeted job, to implement a disjoint set data structure. There are only a few methods that each accomplish a specific task that is described in the .hpp file. Again, the programmer need not concern himself with the how only the what.

Finally this also exemplifies minimization because it is a small targeted piece of code. Also a class is used, which helps prevent data from being accessed. Only the parts of the disjoint set that are meant to be accessed are allowed to be accessed. This minimizes the target area for an exploit in the code.

The driver just does some operations with the disjoint set data structure to show that is works.

The driver is unable to do anything but call the public methods which provide for a controlled environment on the data. Even when DisjointSet is given an invalid input to its functions, it handles it in a documented manner and does not crash.

Nonexample:

There is just one file for the non example of Abstraction, Simplicity, and Minimization. driverBad.cpp. This implements the same disjoint set with the same functionality as the exemplar version. However, the methodology used to write it is completely different.

It does not exemplify abstraction because it is not a template class. It is bound to integers. This has very little flexibility. Also, the functions are right there next to main. all of the information about how things are implemented is readily available. This uses a struct which provides no protection from manipulation of data, nor does it provide a controlled environment. 

It does not exemplify simplicity because all the code is in the way of the user. It uses a global variable to handle data and the functions only modify that global variable. As it stands now, there is no way to create more than one disjoint set in a program. 

Since a struct is used, much more information than is necessary is available. Instead of providing the minimum information to get a job done, the file is cluttered and shows everything about the program. There is no gurantee of maintaining accurate data because the data members can be modified at any time from outside code. 

The driver performs the same operations as the first driver to show that the it does the same thing. So on the surface, it appears that nothing has changed, but with a little digging this code could be exploited because there are no protections against that. It is kind of like using strcpy instead of strncpy. The first version has safeguards to make exploitation difficult. Whereas, this example does not.
