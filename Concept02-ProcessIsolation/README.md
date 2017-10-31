# Concept 02 - Process Isolation
* Code Example: Example1/Exemplar/
* Code NonExample: Example1/NonExample/thread.cpp

## Process Isolation
You want to keep your programs from interacting with each other so they can 
protect themselves from unexpected results of sharing resources. Some tasks 
really do want to influence each other, but it is important to be certain that 
their interactions are necessary as well as facilitated reasonably. 

This generally means keeping memory locations separate. This is usually 
accomplished by creating your separate tasks and processes in a way that allots 
them their own little place in the world. 