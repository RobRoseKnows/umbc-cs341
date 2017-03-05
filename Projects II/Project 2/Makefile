# File:		Makefile
# Name: 	Robert Rose
# Email:	robrose2@umbc.edu
#
# CMSC 341 Spring 2017 Project 1

# ATTENTION GRADER: If you want to quickly run the .sally file I provided,
# simply run `make test` and it'll run it. If you just run `make run`, it
# will prompt you to choose a file. This is a design decision as it makes the
# interperter much more practical.
#
# Alternatively, you can specify any files you want to run as part of the 
# $FILES argument variable of `make run`. For example, in order to run my test
# program, you would run `make run FILES="test.sally"`. Enjoy!

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

test: all
	./a.out test.sally

run: all
	./a.out $(FILES)

fresh: clean run

clean:
	rm -f *.o *.out *~ *.gch
