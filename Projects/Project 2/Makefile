CXX = g++
DEBUG = -g
FLAGS = -ansi -std=c++98 $(DEBUG)
OBJS = Driver.o Game.o CommodityStore.o Objective.o Commodity.o Player.o Card.o

all: $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o a.out

Driver.o: Driver.cpp
	$(CXX) $(FLAGS) -c Driver.cpp

Game.o: Game.cpp Game.h Player.h
	$(CXX) $(FLAGS) -c Game.cpp

CommodityStore.o: CommodityStore.cpp CommodityStore.h
	$(CXX) $(FLAGS) -c CommodityStore.cpp

Objective.o: Objective.cpp Objective.h
	$(CXX) $(FLAGS) -c Objective.cpp

Commodity.o: Commodity.cpp Commodity.h
	$(CXX) $(FLAGS) -c Commodity.cpp

Player.o: Player.cpp Player.h
	$(CXX) $(FLAGS) -c Player.cpp

Card.o: Card.cpp Card.h Commodity.h
	$(CXX) $(FLAGS) -c Card.cpp

val:
	valgrind --leak-check=full ./a.out $(CARDS) $(COMMODITIES) $(PLAYERS) $(STRATEGY)

test: 
	./a.out $(CARDS) $(COMMODITIES)

run:
	./a.out $(CARDS) $(COMMODITIES) $(PLAYERS) $(STRATEGY)

clean:
	rm -f *.o* *~ *.gch
