CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: sudoku

sudoku: sudoku.cpp
	$(CXX) $(CXXFLAGS) sudoku.cpp -o sudoku-solver