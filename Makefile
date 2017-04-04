ifeq "$(shell uname)" "Darwin"
CXX=clang++
else
CXX=g++
endif

ifdef SPEED
CXXFLAGS += -std=c++11 -O3
else
CXXFLAGS += -std=c++11 -Wall -g
endif

solvesudoku: solvesudoku.o SudokuGrid.o Cell.o
	$(CXX) -o solvesudoku solvesudoku.o SudokuGrid.o Cell.o

solvesudoku.o: solvesudoku.cpp SudokuGrid.h Cell.h
	$(CXX) -c $(CXXFLAGS) solvesudoku.cpp

SudokuGrid.o: SudokuGrid.cpp SudokuGrid.h Cell.h
	$(CXX) -c $(CXXFLAGS) SudokuGrid.cpp

Cell.o: Cell.cpp Cell.h
	$(CXX) -c $(CXXFLAGS) Cell.cpp

JUNK=*.o *~ *.dSYM *.gch

clean:
	-rm -rf $(JUNK)

clobber:
	-rm -rf $(JUNK) $(ALL)
