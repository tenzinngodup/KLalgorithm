The KLpartition program.  

ECE 528 
PSU/Fall 2013

Written by Tenzin Ngodup 



Executable File = KLalgorithm
C++ program     = KLalgorithm.cpp
object File     = KLalgorithm.o
Input File      = inputproject.txt
Output File     = output.txt
MakeFile        = makefile
Class Problem Output file = outputclass.txt

To create exe file, type

$make

To execute the project file , type

$ ./KLalgorithm inputproject.txt

To open the output file, type

$ cat output.txt


*****for executing the Hw problem**********


The following program is written in C++ and runs on g++ compiler for Unix 
Machine. 

The folder includes a make file.

INPUT FILE

The default setting for input file is "inputproject.txt" using the project 
40-node input

If you want to compile HW problem, then  you should change line 34: 
     
  
myfile.open ("inputproject.txt"); --> myfile.open ("inputhw.txt");



Then, make the file by typing 

$make 


This compiles the file, then execute the HW file by typing

$ ./KLalgorithm inputhw.txt

To open the output file, type
$ cat output.txt