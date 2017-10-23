# Concept 02 - Process Isolation
* Code Example: Example2/Exemplar
* Code NonExample: Example2/NonExample 

## Example Description
Process Isolation requires that memory spaces for processes be kept seperate. In this example, We have 3 processes, commander, processManager, and reporter. Commander will fork and exec the processManager which will fork and exec the reporter. The processes memory spaces are kept isolated because of the way that fork duplicates processes. All the memory space is copied into seperate newly allocated memory. The parent and child mantain seperate memory spaces. Which is important because when exec is called it overwrites the child's memory with that of the process being executed. If that memory were shared to begin with, it might allow for an exploit into an execed program which is something you might not expect.

## NonExample Description
