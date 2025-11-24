CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

TARGET = chaos
SRC = code/ChaosGame.cpp
OBJ = code/ChaosGame.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

code/ChaosGame.o: code/ChaosGame.cpp
	$(CXX) $(CXXFLAGS) -c code/ChaosGame.cpp -o code/ChaosGame.o

clean:
	rm -f $(TARGET) code/*.o
