# Concept 10 - Minimization
* Code Example: 
  * Example4/DisjointSet.hpp
  * Example4/driver.cpp
* Code NonExample: Example4/driverBad.cpp

----
![minimization](/Concept10-Minimization/minimization.gif)
----

## Example Description
Example 4 driver.cpp exemplifies minimization because it is a small targeted piece of code. A class is used, which helps prevent the inner data from being accessed. Only the parts of the disjoint set that are meant to be accessed are allowed to be accessed. The functions provide for accessing the data in such a way that data integrity is maintained. Because access is limited, the target area for an exploit in the code is minimized.

## NonExample Description
Nonexample 4, driverbad.cpp does not exemplify minimization. Since a struct is used, much more information than is necessary is available. Instead of providing the minimum information to get a job done, the file is cluttered and shows everything about the program. There is no gurantee of maintaining accurate data because the data members can be modified at any time from outside code. The implementation of the disjoint set also does not allow for more than 1 to be created at a time because the functions modify a single global variable. The program cannot be easily expanded upon and has many vectors for exploitation. 
