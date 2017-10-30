# Concept 04 - Domain Seperation
* Code Example: Example1/driver.cpp
* Code NonExample: Example1/driverbad.cpp

----
![DomainSeperation](/Concept01-DomainSeperation/domainseperation.jpg)
----

## Example Description
When creating software, keeping in mind the concept of domain seperation is essential to making secure software. This is often accomplished by creating two or more domains of use. For example, a privileged domain and a user domain are often created to seperate their ability to execute instructions. Often, a privileged state is allowed full control of the system while a user state is only allowed partial control. The distinction between the administrator account and the numerous user accounts exemplifies domain seperation in example1. The administrator account has privileges over the user accounts and provides security through preventing any accidental or intentional changes to other accounts. It is also worth noting that oftentimes the number of accounts with access to elevated privileges is much smaller than the number of of accounts in the user domain. The idea behind that is keeping elevated privileges to a minimum, which provides for a more secure program overall. 


## NonExample Description
