BCXX = g++
DEBUG = -ggdb -g3
FLAGS = -ansi -Wall $(DEBUG)
# My object driver
OBJSDM = Llama.o LlamaNode.o Driver.cpp
# The sample driver one objects
OBJSD1 = driver1.o Llama.o LlamaNode.o
# Sample driver 2 objects
OBJSD2 = driver2.o Llama.o LlamaNode.o
# Sample driver 3 objects
OBJSD3 = driver3.o Llama.o LlamaNode.o OvCoInt.o

dm.out: $(OBJSDM)
	$(CXX) $(FLAGS) $(OBJSDM) -o dm.out

d1.out: $(OBJSD1)
	$(CXX) $(FLAGS) $(OBJSD1) -o d1.out

d2.out: $(OBJSD2)
	$(CXX) $(FLAGS) $(OBJSD2) -o d2.out

d3.out: $(OBJSD3)
	$(CXX) $(FLAGS) $(OBJSD3) -o d3.out

Driver.o: Driver.cpp
	$(CXX) $(FLAGS) -c Driver.cpp

driver1.o: driver1.cpp
	$(CXX) $(FLAGS) -c driver1.cpp

driver2.o: driver2.cpp
	$(CXX) $(FLAGS) -c driver2.cpp

driver3.o: driver3.cpp
	$(CXX) $(FLAGS) -c driver3.cpp

Llama.o: Llama.cpp Llama.h
	$(CXX) $(FLAGS) -c Llama.cpp

LlamaNode.o: LlamaNode.cpp LlamaNode.h
	$(CXX) $(FLAGS) -c LlamaNode.cpp

OvCoInt.o: OvCoInt.cpp OvCoInt.h
	$(CXX) $(FLAGS) -c OvCoInt.cpp

clean:
	rm -f *.o* *~ *.gch
