#I'm experiencing some issues with this and I'm not sure why. If you make any changes to the code, 
# in order to run it you'll first have to run clean. I have no idea why as the new files are being
# created, but they're not reflecting changes to the code.
CXX = g++
DEBUG = -g
FLAGS = -ansi -std=c++98 $(DEBUG)
OBJS = Driver.o AVLNode.o AVLTree.o

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
	
test:
	./a.out

val:
	valgrind --leak-check=full ./a.out $(INPUT) $(RANGE)

run:
	./a.out $(INPUT) $(RANGE)

clean:
	rm -f *.o* *~ *.gch
