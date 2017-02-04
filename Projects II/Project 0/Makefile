# File:		Makefile
# Name: 	Robert Rose
# Email:	robrose2@umbc.edu
#
# CMSC 341 Spring 2017 Project 0
#
# Makefile for compiling the program. The flag it uses is only neccessary for me
# to compile it correctly on my computer.

CXX = g++
DEBUG = -g
FLAGS = -std=c++98
OBJS = joke.o driver.o
TEST_OBJS = joke.o proj0test.o

all: $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o a.out

driver.o: driver.cpp
	$(CXX) $(FLAGS) -c driver.cpp

joke.o: joke.h joke.cpp
	$(CXX) $(FLAGS) -c joke.cpp

proj0test.o: proj0test.cpp
	$(CXX) $(FLAGS)	-c proj0test.cpp

test.out: $(TEST_OBJS)
	$(CXX) $(FLAGS) $(TEST_OBJS) -o test.out

test: test.out
	./test.out

val: all
	valgrind --leak-check=full ./a.out

run: all
	./a.out

fresh: clean run

clean:
	rm -f *.o *.out *~ *.gch
