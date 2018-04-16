###############################################################
# Program:
#     Assignment 12, Hash
#     Brother JonesL, CS235
# Author:
#     Spencer Eccles
#     Jonathan Sirrine
#     Atsushi Jindo
#     Eric Brich
# Summary:
#     <put a description here>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -g
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment12.o     : the driver program
#      spellCheck.o       : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp list.h
	g++ -c $(CPPFLAGS) assignment12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c $(CPPFLAGS) spellCheck.cpp -g

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
	rm a.out assignment12.tar assignment12.o spellCheck.o
clear:
	clear
	clear
test:
	testBed cs235/assign12 assignment12.tar