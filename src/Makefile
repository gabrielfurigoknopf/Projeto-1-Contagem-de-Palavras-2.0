# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall

OBJS = main.o p_input.o
TARGET = contagem_palavras

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp p_input.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

p_input.o: p_input.cpp p_input.hpp
	$(CXX) $(CXXFLAGS) -c p_input.cpp

clean:
	rm -f $(OBJS) $(TARGET)
