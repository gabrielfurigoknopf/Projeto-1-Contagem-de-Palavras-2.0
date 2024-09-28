# Makefile
CXX = g++
CXXFLAGS = -std=c++17

OBJS = main.o
TARGET = contagem_palavras

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp contagem_palavras.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)
