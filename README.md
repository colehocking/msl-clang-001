## Cole Hocking - Operating Systems - MSU Denver - CS3600 - 001 - s17
## Team Indigo
## Assignment C1
## January 6th, 2017

### Synopsis

This program counts the occurrence of words in a text file. It sorts the words lexicographically, using a binary
search tree, and creates an output file with the sorted words, along with the number of times they occurred in the
input file.

This program reads text input from a file with the format "input##.txt", and creates an output file called:
"myoutput##.txt"

### Structures

This program has one struct: a Tree Node (tNode) with a left and right child (pointers to other tree nodes structs),
a char holder for the word in the node, and a counter for the occurrence of the word

### Methods

This program has 4 methods:

##main()
Checks the argument count first. If there are not exactly 2 arguments, the program will terminate.
If 2 arguments do exist, the input filename will be read, and an output file will be created from the input file index.
Main will then call getWord() to parse the file contents for the words. and then delete() to write to the output file
created. The output file is written within the user's working directory.

##getWord()
Obtains the words from the input file. A static definition of space 10 is pre-defined. If the word, along
with the null terminator, is longer than space 10, another space 10 is added to the word, the words are returned as
null-terminate arrays

##insert()
Inserts the words into nodes. If the word exists, only the node's counter is updated. strcmp() is used to
compare the nodes, decide to create a left or right child, and call this method recursively, as well as determine to
only update the counter.

##delete()
Deletes the word and nodes, as well as prints the results to the output file.