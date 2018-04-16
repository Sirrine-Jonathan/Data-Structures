###############################################################
# Program:
#     Assignment 13, Graph
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
a.out: assignment13.o graph.o maze.o
	g++ -o a.out assignment13.o graph.o maze.o -g
	tar -cf assignment13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment13.o     : the driver program
#      graph.o            : the graph code
#      maze.o             : the maze reading and solving code
##############################################################
assignment13.o: graph.h vertex.h assignment13.cpp
	g++ -c assignment13.cpp -g

graph.o: graph.h set.h vertex.h graph.cpp
	g++ -c graph.cpp -g

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -c maze.cpp -g

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
	rm a.out assignment13.tar assignment13.o graph.o maze.o
clear:
	clear
	clear
test:
	testBed cs235/assign13 assignment13.tar