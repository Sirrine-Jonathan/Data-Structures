###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother JonesL, CS235
# Author:
#     Spencer Eccles
#     Jonathan Sirrine
#     Atsushi Jindo
#     Eric Brich
# Summary:
#     <put a description here>
# Time:
#     Group: 3hrs
#     Spencer Eccles: 15m
#     Jonathan Sirrine
#     Atsushi Jindo
#     Eric Brich 10hr
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c $(CPPFLAGS) assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c $(CPPFLAGS) nowServing.cpp
##############################################################
# We play by MY rules!
##############################################################
rm:
	rm a.out assignment04.tar assignment04.o nowServing.o

test:
	testBed cs235/assign04 assignment04.tar

