###############################################################
# Program:
#     Assignment 10, Map
#     Brother JonesL, CS 235
# Author:
#     <your name here>
# Summary:
#     Spencer Eccles
#     Jonathan Sirrine
#     Atsushi Jindo
#     Eric Brich 
# Time:
#     <how long did it take to complete this program?>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g

##remove map.h from wordCount.o dependencies
wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g 
##############################################################
# We play by MY rules!
##############################################################
m:
	clear
	clear
	make
rm:
	clear
	clear
	rm a.out assignment10.tar assignment10.o wordCount.o
clear:
	clear
	clear
test:
	testBed cs235/assign10 assignment10.tar