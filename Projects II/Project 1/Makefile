# File:		Makefile
# Name: 	Robert Rose
# Email:	robrose2@umbc.edu
#
# CMSC 341 Spring 2017 Project 1

CXX = g++
DEBUG = -g
CPPFLAGS = -std=c++98 $(DEBUG)
OBJS = Graph.o Driver.o

all: $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o a.out

test1.out: Graph.o test1.o
	$(CXX) $(FLAGS) Graph.o test1.o -o test1.out

test2.out: Graph.o test2.o
	$(CXX) $(FLAGS) Graph.o test2.o -o test2.out

test1: test1.out
	./test1.out

test2: test2.out
	./test2.out

val: all
	valgrind --leak-check=full ./a.out

run: all
	./a.out

fresh: clean run

clean:
	rm -f *.o *.out *~ *.gch
