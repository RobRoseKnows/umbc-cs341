CXX = g++
DEBUG = -g
FLAGS = -ansi -std=c++98 $(DEBUG)
OBJS = Driver.o AVLForest.o AVLNode.o AVLTree.o

all: $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o a.out

Driver.o: Driver.cpp
	$(CXX) $(FLAGS) -c Driver.cpp

AVLForest.o: AVLForest.cpp AVLForest.h
	$(CXX) $(FLAGS) -c AVLForest.cpp

AVLNode.o: AVLNode.cpp AVLNode.h
	$(CXX) $(FLAGS) -c AVLNode.cpp

AVLTree.o: AVLTree.cpp AVLTree.h AVLTreeBase.h
	$(CXX) $(FLAGS) -c AVLTree.cpp

val:
	valgrind --leak-check=full ./a.out $(INPUT) $(RANGE)

run:
	./a.out $(INPUT) $(RANGE)

clean:
	rm -f *.o* *~ *.gch
