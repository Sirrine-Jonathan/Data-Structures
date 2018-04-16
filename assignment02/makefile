###############################################################
# Program:
#     Assignment 02, STACK
#     Brother JonesL, CS235
# Authors:
#     Spencer Eccles
#     Jonathan Sirrine
#     Atsushi Jindo
#     Eric Brich
# Summary:
#     <put a description here>
# Hardest Part:
#     Spencer Eccles:
#     Jonathan Sirrine:
#     Atsushi Jindo
#     Erich Brich
# Group Time Spent: 3 hours
# Individual Time Spent:
#     Spencer Eccles: 5m + 2:04PM-
#     Jonathan Sirrine: 
#     Atsushi Jindo
#     Erich Brich
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp
rm:
	rm a.out assignment02.tar infix.o assignment02.o
test:
	testBed cs235/assign02 assignment02.tar
