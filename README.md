# Cplusplus_Bank_Project

In tproject2 I encountered some new problems in my code other than issues noted as comments from project1. 
I found a logic gap in the delete method which was a quick fix. Essentially if I had one item in the list and 
selected to remove a greater but non-existent file number then I would dereference a null pointer and crash, so I
added an if statement to accomodate that case. I also changed read and writefile, so that they simple read until
an empty line or end of file occurs instead of reading until an asterisk was present as I had done in project1

Hangbo had made a comment about the structure of find record. He said the method should exit immediately after an 
incorrect file number had been entered, as mine originally requested for a correct file number leaving you
in a loop within the find record method. I fixed this problem in find and noticed that delete record was 
structured the same way so I also changed the issue there as well. 

I changed my make file to compile and link the files separately instead of including the database function in the 
user interface function as I did in project1.

- Overloading the equivalence operator/ copy constructor 
These two extra credit assignments were practically identicaly in logic and I did not run into any major issues while
devoloping or implementing these. I ran into one issue with the copy constructor. I forgot to create new llist 
object with every iteration of the loop and this initially cause some problems with implementation which were fixed 
and extended across both methods because both the copy constructor and overloaded equivalence operator could 
potentially run into trouble around this issue. 

- overloading the << operator
I wrote the code for this method but so far I have struggled with implementation because ostream and std::cout are
not recognized as a type in C++ I am not sure how to overcome this issue because it is critical to the structure of
the method and my research on the matter has not gotten me very far. The internet suggested that I make sure that
<iostream> is included on every file in which any reference to the methoid occurs which I did; however, despite 
despite ostream being subservient to iostream g++ still does not recognize ostream& as a return type.
