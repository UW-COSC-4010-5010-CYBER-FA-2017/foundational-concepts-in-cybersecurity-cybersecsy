# Concept 10 - Minimization

## Example Description
Example 3's driver exemplifies minimization because it is a small targeted 
piece of code. The disjoint set class implements the functionality using a small 
amount of code and it doens't do more than it needs to. A class is used, which 
helps prevent the inner data from being accessed. Only the parts of the disjoint 
set that are meant to be accessed are allowed to be accessed. The functions 
provide for accessing the data in such a way that data integrity is maintained. 
Also because the code for the disjoint set class is in a seperate file, the 
driver is kept clean, manageable and small. Since access to the private data 
members of the disjoint set is limited, the target area for an exploit in the 
code is minimized.

## NonExample Description
Nonexample 3's driver does not exemplify minimization. Since a struct is 
used, much more information than is necessary is available. Instead of providing 
the minimum information to get a job done, the file is cluttered and shows 
everything about the program. None of the code is seperated from the source 
file, which clutters main and overall, makes it less organized and readable. 
There is no guarantee of maintaining accurate data because the data members can 
be modified at any time from outside code. The implementation of the disjoint 
set also does not allow for more than one set to be created at a time because the 
functions modify a single global variable. The program cannot be easily expanded 
upon, shows much more information than is necessary, and has many vectors for 
exploitation. 

----
![minimization](/Concept10-Minimization/minimization.jpg)
----
