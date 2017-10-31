# Concept 04 - Least Privilege

## Example Description
The concept of least privilege is based on the idea of giving a user or a 
process the least amount of power possible, while still being able to complete 
the task at hand. This is done to prevent any accidental or intential breaches 
of security. This program creates a single administrator account which has 
elevated privileges over the other regular user accounts. The administrator can 
create and delete regular accounts, but the normal user accounts only have the 
ability to change their own password. This is because a regular user has no 
reason to have the ability to add or delete other users. 

## NonExample Description
We see that the concept of least privilege has been blown out of the water in 
this nonexample. Here, a user can access anything they please. Since it gives 
all of the users the power to delete and create other users, nobody can have 
safe data anymore. For good measure, I included a print-out of the current users 
on the machine as well as their passwords. Someone's password can be easily 
hacked, so someone with ill-intent would likely have all of this information and 
therefore complete control of the machine. 

----
![LeastPrivilege](/Concept04-LeastPrivilege/leastprivelege.gif)
----