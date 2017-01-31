CXX = g++
DEBUG = -g
FLAGS = -ansi -std=c++98 $(DEBUG)
OBJS = Driver.o PinHit.o Heap.o MaxHeap.o MinHeap.o

all: $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o a.out

Driver.o: Driver.cpp
	$(CXX) $(FLAGS) -c Driver.cpp

PinHit.o: PinHit.cpp PinHit.h
	$(CXX) $(FLAGS) -c PinHit.cpp

Heap.o: Heap.cpp Heap.h
	$(CXX) $(FLAGS) -c Heap.cpp

MaxHeap.o: MaxHeap.cpp MaxHeap.h
	$(CXX) $(FLAGS) -c MaxHeap.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	$(CXX) $(FLAGS) -c MinHeap.cpp
	
test:
	./a.out Input1.txt --max

val:
	valgrind --leak-check=full ./a.out $(INPUT) $(FLAG)

run:
	./a.out $(INPUT) $(FLAG)

clean:
	rm -f *.o* *~ *.gch
