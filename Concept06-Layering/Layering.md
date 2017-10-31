# Concept 06 - Layering

## Example Description
In the example, there is both a password for each user to log on with, as well 
as a privilege level associated with each user. This allows for data to be 
protected both by a password as well as system limitations on non-admin users. 
Further, the code itself employs multiple different security measures. Not only 
does it facilitate resource use through properly scoping variables (at least 
compared to the nonexample), but it also separates out functionality, making 
the code simpler to understand and less prone to security mistakes. 

## NonExample Description
In this nonexample, we show the exact opposite of what is stated above. There 
is a password, but that is it. Therefore, if someone where to spoof a password, 
the whole system would be compromised. Further, the code uses unnecessary 
global variables and is all smashed together in main, making it more difficult 
to understand and more prone to security mistakes. Notice that the user is 
asked to verify their password before adding or deleting another user. This is 
*not* a form of layering security since someone who has gotten that far into 
the system already knows your password, and therefore isn't hindered by a second 
security measure of the same type as the first. 

----
![Layering](/Concept06-Layering/layers.mp4)
----