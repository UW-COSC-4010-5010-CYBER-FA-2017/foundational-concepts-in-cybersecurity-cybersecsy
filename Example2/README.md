#Example 2
Domain Separation(1), Least Privilege(4), Layering(6), Data Hiding(8) 

## Exemplar:
    make example2

This program emulates a log in process for users. It is a simple implementation that aims to show the differences in prileges and the the different types of security. The administrator account can create and delete regular users. However, the normal user does not have that power. They can only logout and change their own password. Passwords are not stored as hashes, simply because this is a small program meant to emulate behavoir rather than recreate it. Part of that, is not saving any of the data. All "users" are just stored in memory and lost when the program is terminated. 
 

### Running the Example:
    ./example2
This program is a bit different from the others in that it will require a bit of interaction while running it. the onscreen prompts are pretty self explanatory. The first thing that occurs when running the program is the creation of a single administrator account. After that, you can login as the administrator and create and delete regular user accounts.


## NonExample:

### Running the Example:
