###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother JonesL, CS235
# Author:
#     Spencer Eccles
#     Jonathan Sirrine
#     Atsushi Jindo
#     Eric Brich 
# Summary:
#     Builds bst.h and bnode.h
# Time:
#     10 hrs
###############################################################

##############################################################
# The main rule
##############################################################
all: a.out b.out

a.out: assignment09.o
	g++ -o a.out assignment09.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

b.out: DiscussionPostDriver.o
	g++ -o b.out DiscussionPostDriver.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bnode.h bst.h assignment09.cpp
	g++ -c assignment09.cpp -g

DiscussionPostDriver.o: bnode.h bst.h DiscussionPostDriver.cpp
	g++ -c DiscussionPostDriver.cpp -g

##############################################################
# We play by MY rules!
##############################################################
rm:
	clear
	clear
	rm a.out assignment09.tar assignment09.o DiscussionPostDriver.o
clear:
	clear
	clear
test:
	testBed cs235/assign09 assignment09.tar

