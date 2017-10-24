# Concept 07 - Abstraction
* Code Example: 
  * Example4/DisjointSet.hpp
  * Example4/driver.cpp
* Code NonExample: Example4/driverBad.cpp


## Example Description
This program exemplifies abstraction mainly because it utlizes a template class and a uses private data members all of which are decoupled from the driver. Since it is templated, any data type can be used with the class. This allows for very easy and bug free expansion later, which will help keep the program secure. This also sepereates the design from the implementation. The client doesn't need to know how various functions are implemented. Only the behavior of the functions is necessary for a programmer to use the DisjointSet data structure. This also allows for the implementation to be changed without the client code ever knowing. The data members are also private which means they are "hidden" from the client. They can't be accessed except in a controlled manner. And the client doesn't even need to know about how the underlying data is stored and maintained.

## NonExample Description
This program does not exemplify abstraction because it is not a template class, the design is coupled to the implementation and there is no abtstract representation of an object, rather just a bunch of code slammed together right by main. It is bound to integers and so has very little flexibility and a very specific use case.  It can't be easily expanded upon and so makes bug free additions very hard. Also, None of the information about the implementation is hidden, making it very easy to find the holes in the code. A struct is also used, which provides no protection for the data members of the disjointSet. This makes data consistency impossible to guarantee. At any time, data members can be changed by the client since a controlled environment is not provided. Overall this allows for many exploits. 
