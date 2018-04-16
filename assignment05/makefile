###############################################################
# Program:
#     Assignment 05, SET
#     Brother JonesL, CS235
# Author:
#    Spencer Eccles
#    Jonathan Sirrine
#    Atsushi Jindo
#    Eric Brich 4hrs
# Summary:
#     Makes a.out for assignment
#     Makes b.out for custom tests
# Time:
#     Pair Programming: 6hrs
# Hardest Part:
#	  Most difficult part was test 5 and 7
#	  Changing the difference operator was a challenge
###############################################################

##############################################################
# The main rule
##############################################################
all: a.out b.out

a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

b.out: customTest.o
	g++ -o b.out customTest.o

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c $(CPPFLAGS) assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c $(CPPFLAGS) goFish.cpp

card.o: card.h card.cpp
	g++ -c $(CPPFLAGS) card.cpp 

##############################################################
# Test obj file
#      customTest.o   : test driver program
##############################################################

customTest.o: set.h customTest.cpp
	g++ -c -DDEBUG set.h customTest.cpp

##############################################################
# We play by MY rules!
##############################################################
rm:
	rm a.out
	rm b.out
	clear

test:
	testBed cs235/assign05 assignment05.tar

