# You have to clear before you can compile a second time, I don't know why but that's
# what's happening. I was unable to run valgrind on this because I don't have it
# working in WSL and I got locked out of my home directory via WinSCP.

CXX = g++
DEBUG = -g
FLAGS = -ansi -std=c++98 $(DEBUG)

test: Driver.o Pinball.o
	$(CXX) $(FLAGS) Driver.o Pinball.o -o a.out

med_test: MedTest.o Pinball.o
	$(CXX) $(FLAGS) MedTest.o Pinball.o -o med.out

small_test: SmallTest.o Pinball.o
	$(CXX) $(FLAGS) SmallTest.o Pinball.o -o small.out

Driver.o: driver.cpp
	$(CXX) $(FLAGS) -c driver.cpp

MedTest.o: mediumtest.cpp
	$(CXX) $(FLAGS) -c mediumtest.cpp

SmallTest.o: smalltest.cpp
	$(CXX) $(FLAGS) -c smalltest.cpp

Pinball.o: Pinball.cpp Pinball.h
	$(CXX) $(FLAGS) -c Pinball.cpp

val:
	valgrind --leak-check=full ./a.out

run:
	./a.out $(INPUT) $(FLAG)

clean:
	rm -f *.o* *~ *.gch
