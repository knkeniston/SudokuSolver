#include <iostream>
#include <string>
#include <sstream>
#include "SudokuGrid.h"
#include "Cell.h"

/* Kelly Kensiston, CS 355, Spring 2016
	This class represents a SudokuGrid object. It implements the ability
	to create a Sudoku puzzle from a string as a private method. It supports
	several public methods for getting information from and modifying the
	Sudoku puzzle. */

/* Constructor that creates initial puzzle from an input string as described in 
	Section 4.1. */
SudokuGrid::SudokuGrid(std::string s) {
	stringToGrid(s);
}

/* Turns the string passed in into a Sudoku grid. */
void SudokuGrid::stringToGrid(std::string s) {
	int row = 1;
	int col = 1;
	for (int i = 0; i <= 9; i++) {
		grid[0][i] = Cell(0, false, false);
	}
	for (char& c : s) {
		if (c == '\n') { break; }
		if (col == 10) {
			col = 1;
			row++;
		}
		if (c == '.') {
			Cell cell = Cell(0, false, false);
			grid[row][col] = cell;
		} else {
			Cell cell = Cell(c - '0', true, true);
			grid[row][col] = cell;
		}
		col++;
	}
}

/* Read number at  grid location (row, col). Returns 0 for empty cell. */
int SudokuGrid::number(int row, int col) const {
	return grid[row][col].cellVal();
}

/* Set number at grid location (row, col). Use num = 0 to clear value. */
void SudokuGrid::setNumber(int row, int col, int num) {
	if (!grid[row][col].isFixed()) {
		grid[row][col].setCellValue(num);
	}
}

/* number at grid location (row, col) is original "fixed" value. */
bool SudokuGrid::isFixed(int row, int col) const {
	return grid[row][col].isFixed();
}

/* Cell at (row, col) has been marked as solved. */
bool SudokuGrid::isSolved(int row, int col) const {
	return grid[row][col].isSolved();
}

/* Mark the cell at (row, col) has having been solved.*/ 
void SudokuGrid::setSolved(int row, int col) {
	grid[row][col].setSolved(true);
}

/* Is value 1 <= n <= 9 penciled into the cell at (row, col)? */
bool SudokuGrid::isPencilSet(int row, int col, int n) const {
	return grid[row][col].isPencilSet(n);;
}

/*Are any values at cell (row, col) penciled in? */
bool SudokuGrid::anyPencilsSet(int row, int col) const {
	return grid[row][col].anyPencilSet();
}

/* Set pencil n in cell (row, col) */
void SudokuGrid::setPencil(int row, int col, int n) {
	grid[row][col].setPencil(n, true);
}

/* Set all nine pencil values in cell (row, col) */ 
void SudokuGrid::setAllPencils(int row, int col) {
	grid[row][col].setAllPencils(true);
}

/* Clear pencil n in cell (row, col) */
void SudokuGrid::clearPencil(int row, int col, int n) {
	grid[row][col].setPencil(n, false);
}

/* Clear all pencil values in cell (row, col) */
void SudokuGrid::clearAllPencils(int row, int col) {
	grid[row][col].setAllPencils(false);
}
