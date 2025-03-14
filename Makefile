CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Werror -Wextra -Wfatal-errors -pedantic -Iinclude

all: d l

d: src/dijkstras_main.cpp src/lib/dijkstras.o
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp src/lib/dijkstras.o -o dijkstras_main
l: src/ladder_main.cpp src/lib/ladder.o
	$(CXX) $(CXXFLAGS) src/ladder_main.cpp src/lib/ladder.o -o ladder_main

src/lib:
	mkdir -p src/lib

src/lib/dijkstras.o: src/dijkstras.cpp src/dijkstras.h 
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o src/lib/dijkstras.o
src/lib/ladder.o: src/ladder.cpp src/ladder.h 
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o src/lib/ladder.o

clean:
	rm -f src/lib/*.o ladder_main dijkstras_main