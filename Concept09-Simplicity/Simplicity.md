# Concept 09 - Simplicity

## Example Description
This program exemplifies simplicity in that it has a very targeted job, to 
implement a disjoint set data structure. There are only a few methods that each 
accomplish a specific task that is described in the .hpp file. There isn't any 
unecessary code cluttering up the driver file or extra unecessary features in 
the disjoint set class. This helps keep the program smaller and thus creates a 
smaller vector for exploitation in the future. It also minimizes the amount of 
bugs that go unnoticed. The class also uses private data members which helps 
keep the data members in good condition. These few functions provide all the 
functionality of the disjoint set class, which makes it easy to test and keeps 
the program simple.

## NonExample Description
This program does not exemplify simplicity because all the code is cluttered 
about in the driver. The program becomes more complicated to follow and thus 
harder to debug. This allows for more bugs to make it past the developer which 
increases the potential for exploitation later. It uses a global variable to 
handle data and the functions only modify that global variable. Not only does 
this not provide and checks or protections against mistaken changing of the 
data, it also provides an easy way for an attacker to exploit the code. As it 
stands now, there is no way to create more than one disjoint set in the program. 
The program would have to grow tremendously in size in order to have a second 
disjoint set. It would require many edits which, in turn, introduces many new 
bugs. Very quickly, the program would grow large and the potential security 
risks grow with it.

----
![Simplicity](/Concept09-Simplicity/simplicity.gif)
----
