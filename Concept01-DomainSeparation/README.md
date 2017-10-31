# Concept 01
* Code Example: Example2/driver.cpp
* Code NonExample: Example2/driverbad.cpp

## Domain Separation
Keeping distinct entities separate from one another is key to domain separation. 
You never want to allow a free for all on resource usage. Good fences really do 
make good neighbors. 

Domain seperation is essential to making secure software. This 
is often accomplished by creating two or more domains of use. For example, a 
privileged domain and a user domain are often created to seperate their ability 
to execute instructions. Often, a privileged state is allowed full control of 
the system while a user state is only allowed partial control.
