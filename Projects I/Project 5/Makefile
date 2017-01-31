CXX = g++
DEBUG = -g
FLAGS = -ansi -std=c++98 $(DEBUG)

test: driver.o Pinball.o
	$(CXX) $(FLAGS) driver.o Pinball.o -o a.out

med_test: MedTest.o Pinball.o
	$(CXX) $(FLAGS) MedTest.o Pinball.o -o med.out

small_test: SmallTest.o Pinball.o
	$(CXX) $(FLAGS) SmallTest.o Pinball.o -o small.out

driver.o: driver.cpp
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
