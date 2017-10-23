# Concept 09 - Simplicity
* Code Example: 
  * Example4/DisjointSet.hpp
  * driver.cpp
* Code NonExample: Example4/driverBad.cpp


## Example Description
This program exemplifies simplicity in that it has a very targeted job, to implement a disjoint set data structure. There are only a few methods that each accomplish a specific task that is described in the .hpp file. The class uses private data members which helps keep the data members in good condition. The few functions provide all the functionality of the disjoint set class and keep the program simple.

## NonExample Description
This program does not exemplify simplicity because all the code is in the way of the user. It uses a global variable to handle data and the functions only modify that global variable. As it stands now, there is no way to create more than one disjoint set in the program. To have a second disjoint set would require a lot more code and many edits to the current code. very quickly, the program would grow large and very far from simple.
