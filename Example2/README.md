# Example 2
Domain Separation(1), Least Privilege(4), Layering(6), Data Hiding(8) 

## Exemplar:
    make example2

This program emulates a log in process for users. It is a simple implementation 
that aims to show the differences in privileges and the the different types of 
security. The administrator account can create and delete regular users. 
However, the normal user does not have that power. They can only logout and 
change their own password. Passwords are not stored as hashes, simply because 
this is a small program meant to emulate behavoir rather than recreate it. Part 
of that, is not saving any of the data. All "users" are just stored in memory 
and lost when the program is terminated. 
 

### Running the Example:
    ./example2

When you run the program, it will prompt you to create an administrator with a 
password. From there, you can log in or exit the system. If you exit, all data 
is lost. Once you log on, the administrator has 4 options. You can create a 
user, delete a user, or change your password. The admin can't create another 
administrator and there are only 5 users allowed including the admin. This will 
also check other usernames and won't allow for duplicate usernames. When the 
admin creates or deletes a user, a list of users is printed. It will always 
create a new user in the earliest available spot. So if you create user1, user2, 
and user3, then delete user2, the next user will fill the user2 spot in the 
array. You can log out of admin and log in to other users. Regular users can 
only change their password or logout. They can't even delete their own user 
account.  


## NonExample:
    make nonexample2
    
This program is a simulation of a log in process for users on a system without 
an admin. It is a literal free-for-all and anyone who is logged in has the 
power to delete anyone else. It doesn't even check to see if two users have the 
same name. In fact, if you want to delete a user, it will delete any user with 
that 
name and doesn't check for duplicate names upon adding a user. It even prints 
user information including their passwords frequently. 


### Running the Example:
    ./nonexample2
    
This will run much like the example, except you don't create an admin. Instead 
you create the first user and from there everyone has the same options as the 
admin did in the example above. Unlike the example above, this program will not 
check to see how many users you have created.... but it will seg fault if you 
go over the limit. Further, it won't try to fill empty spots like the example 
above. If you create u1, u2, and u3, then delete u4, the next user will not be 
created where u2 was... it will take up it's own spot in memory and let u2's 
information sit instead. 
