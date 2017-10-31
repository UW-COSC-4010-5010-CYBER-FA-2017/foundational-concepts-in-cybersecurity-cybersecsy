# Concept 08 - Data Hiding

## Example Description
This program exmplifies Data Hiding because only the administrator has access 
to certain information. Further, the functions are parsed out so only certain 
information is available at certain times. For instance, there is a separate 
function to prompt the user to add a client and read in their input and a 
separate function to actually create that client. If this were a larger 
program, this would likely be hooked up to a database and breaking up functions 
like this helps protect SQL injection. This could be expanded into .h and .cpp 
files to provide even more data hiding as well. 

## NonExample Description
This is about as bad as it gets for data hiding... because there is none. Anyone 
has access to any data at anytime. Furthermore, most of the data is stored in 
global variables that are ready for an attacker to access the entire time the 
system is up. Worse then that, all of this is just sitting in main. No parsing 
out into other functions at all. And it gets worse.... because it prints out 
user information including passwords. It's not just failing at hiding the 
information, it's giving it away for free. 

----
![hide](https://media.giphy.com/media/hHuOmWidPXwCk/giphy.gif)
----