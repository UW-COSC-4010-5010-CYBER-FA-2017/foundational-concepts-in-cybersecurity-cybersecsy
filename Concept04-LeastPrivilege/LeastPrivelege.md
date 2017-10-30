# Concept 04 - Least Privilege
* Code Example: Example1/driver.cpp
* Code NonExample: Example1/driverbad.cpp

----
![LeastPrivilege](/Concept04-LeastPrivilege/leastprivelege.gif)
----

## Example Description
The concept of least privilege is based on the idea of giving a user or a process a least amount of power possible, while still being able to complete the job/s at hand. This is done to prevent any accidental, or intential breaches of security. This program creates a single administrator account which has elevated privileges over the other regular user accounts. For example, it can create and delete regular accounts. However, the normal user accounts only have the ability to change their own password. This could be expanded upon to include any number of elevated abilities and non elevated abilities. Each user can accomplish thier tasks without having the full power of an administrator account. 

## NonExample Description
