#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <array>
#include <bitset>
#include <string>
#include "Cell.h"

class SudokuGrid {
	private:
		std::array<std::array<Cell,10>,10> grid;
		void stringToGrid(std::string s);
	public:
		SudokuGrid(std::string s); // constructor

		int number(int row, int col) const;
		void setNumber(int row, int col, int number);
		bool isFixed(int row, int col) const;
		bool isSolved(int row, int col) const;
		void setSolved(int row, int col);

		bool isPencilSet(int row, int col, int n) const;
		bool anyPencilsSet(int row, int col) const;
		void setPencil(int row, int col, int n);
		void setAllPencils(int row, int col);
		void clearPencil(int row, int col, int n);
		void clearAllPencils(int row, int col);
};


#endif // SUDOKUGRID_H
