# Concept 05 - Modularity
* Code Example: Example2/Exemplar/
* Code NonExample: Example2/NonExample/thread.cpp

----
![Modularity](/Concept05-Modularity/modularity.gif)
----

## Example Description
This is a very modular program. 3 distinct process work together with minimal information exchanged between them. In fact, you have to the ability to complete change the manner in which one of these proccesses accomplishes its task without even modifing the other two programs(provided it takes the same data to complete the task). Pipes are used to communicate data between these processes which provide an easy interface to access data from. However, how the data is manipulated by the process is completely self contained. 

The QueueArray class also makes this a modular program in a similar manner. Without changing the function declrations, you can change the function definitions to do perform the same task in a different manner, or even perform a different task all together, with no changes to the rest of the program. Theoretically, provided function delcarations are consisent, you should be able to substitute someone else's QueueArray class and change nothing else in the program and it all will still work. That is Modularity. 

## NonExample Description

Going along with the idea of encapsulating the arrays used in this program, that would also allow for some modularity. As it stands now, there is one cpp file. Nothing is seperated from main and there is no easy way to change anything, without changing most of it. You cannot remove pieces, you cannot change only the implementation of pieces. It is all tied together and very much not modular. If you were to encapsulate the arrays used in a data structure, you could begin to decouple the design from the implementation which creates modular code. With this, you can remove or change parts of the implementation of a particular piece of code without changing anything else. 