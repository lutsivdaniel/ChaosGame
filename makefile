CXX = g++
CXXFLAGS = -std=c++17
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: chaos

chaos: code/ChaosGame.cpp
	$(CXX) $(CXXFLAGS) code/ChaosGame.cpp -o chaos $(SFML)

clean:
	rm -f chaos