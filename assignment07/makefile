###############################################################
# Program:
#     Assignment 07, LIST
#     Brother JonesL, CS235
# Author:
#    Spencer Eccles
#    Jonathan Sirrine
#    Atsushi Jindo
#    Eric Brich 10h+
# Summary:
#     The fibonacci was by far the hardest. We got a working
#     method, but it doesn't support numbers that go past
#     ints. So at number 47 there are too many values for
#     a regular int.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o wholeNumber.o
	g++ -o a.out assignment07.o fibonacci.o wholeNumber.o -g  -std=c++11
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
assignment07.o: list.h assignment07.cpp
	g++ -c assignment07.cpp -g  -std=c++11

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp -g  -std=c++11

wholeNumber.o: wholeNumber.h wholeNumber.cpp list.h
	g++ -c wholeNumber.cpp -g  -std=c++11

##############################################################
# We play by MY rules!
##############################################################
rm:
	rm a.out assignment07.tar assignment07.o fibonacci.o wholeNumber.o
	clear
	make

test:
	testBed cs235/assign07 assignment07.tar