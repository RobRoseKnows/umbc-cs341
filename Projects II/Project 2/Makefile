# File:		Makefile
# Name: 	Robert Rose
# Email:	robrose2@umbc.edu
#
# CMSC 341 Spring 2017 Project 1

CXX = g++
DEBUG = -g
CPPFLAGS = -std=c++98 $(DEBUG)
PRIM_OBJS = Sally.o Driver.o
D1_OBJS = Sally.o driver1.o
D2_OBJS = Sally.o driver2.o

all: $(PRIM_OBJS)
	$(CXX) $(FLAGS) $(PRIM_OBJS) -o a.out

driver1.out: $(D1_OBJS)
	$(CXX) $(FLAGS) $(D1_OBJS) -o driver1.out

driver2.out: $(D2_OBJS)
	$(CXX) $(FLAGS) $(D2_OBJS) -o driver2.out

driver1: driver1.out
	./driver1.out

driver2: driver2.out
	./driver2.out

val: all
	valgrind --leak-check=full ./a.out

run: all
	./a.out $(FILES)

fresh: clean run

clean:
	rm -f *.o *.out *~ *.gch
