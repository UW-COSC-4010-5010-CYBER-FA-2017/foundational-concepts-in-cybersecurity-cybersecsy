# Concept 05 - Modularity

## Example Description
This is a very modular program. 3 distinct process work together with minimal 
information exchanged between them. In fact, you have the ability to completely 
change the manner in which one of these proccesses accomplishes its task 
without even modifing the other two programs (provided it takes the same data 
to complete the task). Pipes are used to communicate data between these 
processes which provide an easy interface to share data. However, how the data 
is manipulated by the process is completely self contained. 

The QueueArray class also makes this a modular program in a similar manner. 
You can change the function definitions to perform the same task in a different 
way, or even perform a different task all together, without any changes to the 
rest of the program, even including the function declarations. Provided the
function delcarations are consisent, you can substitute someone 
else's QueueArray class and change nothing else in the program and it all will 
still work.

## NonExample Description
This entire program is held in one single .cpp 
file. Nothing is seperated from main and there is no easy way to change 
anything, without cascading effects across the rest of the file. You cannot 
easily remove or change parts. It is all 
tied together and not modular. If you were to encapsulate the arrays 
used in a data structure, you could begin to decouple the design from the 
implementation which creates modular code. With this, you can remove or change 
parts of the implementation of a particular code segment without changing 
anything else. 

----
![Modularity](/Concept05-Modularity/modularity.gif)
----