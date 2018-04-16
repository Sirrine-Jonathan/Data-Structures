###############################################################
# Program:
#     Assignment 06, NODE
#     Brother JonesL, CS235
# Author:
#    Spencer Eccles
#    Jonathan Sirrine
#    Atsushi Jindo
#    Eric Brich 8h
# Summary:
#     Most difficult part is the remove function
#	  It seems to seg fault a lot
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o  -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g

##############################################################
# We play by MY rules!
##############################################################
rm:
	rm a.out
	clear
	make

test:
	testBed cs235/assign06 assignment06.tar
