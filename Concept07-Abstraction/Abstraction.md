Concept 07 - Abstraction

Code Example:
Example 4

Example 4 driver.cpp exemplifies abstraction mainly because it is a template class and a uses private data members. Since it is templated, any data type can be used with the class. This helps sepereate the design from the implementation. The client doesn't need to know how various functions are implemented, Only the behavior of the functions is necessary for a programmer to use the DisjointSet data structure. Since the data members are private, they are "hidden" from the client, in that they can't be accesses except in a controlled manner.

nonExample 4 driverBad.cpp does not exemplify abstraction because it is not a template class. It is bound to integers. This has very little flexibility and a very specific use case.  Also, the functions are right there next to main. None of the information about the implementation is hidden. A struct is also used, which provides no protection for the data members of the disjointSet. This makes data consistency impossible to guarantee. At any time, data members can be changed by the client. This also does not provide a controlled environment and allows for exploits. 
