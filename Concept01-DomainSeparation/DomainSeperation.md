# Concept 01 - Domain Separation

## Example Description
We show domain seperation in *Example 2* by having separate functionality for 
the administrator and the rest of the users. The administrator account has 
privileges, like adding and deleting other users, that the user accounts can't 
access. This provides security through preventing any accidental or intentional 
changes to other accounts. The number 
of accounts with access to elevated privileges is much smaller than the number 
of of accounts in the user domain to keep elevated privileges to a minimum, 
which provides for a more secure program overall. We also support this concept 
by keeping few global variables and separating the program itself into separate 
functions which have access to their own resources. 


## NonExample Description
We show what can happen when domain separation is ingnored in *Nonexample 2*. 
By allowing all of the users to have the same privelages, you allow any user to 
create or delete any other user. In the example we provide a 1:4 ratio on 
elevated privelages... but not here. Here we don't even check the number of 
users, resulting in a segmentation fault if you go over. We also have a ton of 
global variables, supporting a notion of free-for-all usage of information. 
Further, we throw everything into main and let every part of the program share 
resources with every other part. 

----
![DomainSeparation](/Concept01-DomainSeparation/domainseperation.jpg)
----