# Concept 03
* Code Example: Example1/Exemplar/
* Code NonExample: Example1/NonExample/thread.cpp 

## Resource Encapsulation
Each part of your system should be isolated. This way, if there is a security 
breach, it isn't winner-take-all. When you have isolated processes/tasks, you 
shorten the attack area to that one process/task. 

This is usually accomplished by keeping your programs running as independently 
as possible with strict data access rules. This keeps information isolated. 
Further, choosing the correct data types and scopes for your variables and more 
complex data structures plays a huge part. You want to make these decisions 
deliberately. 