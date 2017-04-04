#include <string>
#include <iostream>
#include <algorithm>
#include "SudokuGrid.h"

/* Kelly Kensiston, CS 355, Spring 2016
	This program takes in a string from the console and turns it into
	a Sudoku game. It prints out the original unsolved puzzle, solves
	it, and then prints out the solved puzzle. */

using namespace std;

/* Searches entire Sudoku grid, returns true if it finds an empty
	cell. Modifies the row and col pointers to point to that cell. */
bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col) {
	for (int i = 1; i <= 9; i++) { // i = row
		for (int j = 1; j <= 9; j++) { // j = col
			if (grid.number(i, j) == 0) {
				row = i; col = j;
				return true;
			}
		}
	}
	return false;
}

/* Checks the row, column, and block of the cell of the position (row, col)
	passed in. If the row, column, or block has a cell with the same 
	number as the number passed in, returns true. If not, returns false. */
bool conflictingNumber(SudokuGrid& grid, int row, int col, int num) {
	// check row and column
	for (int i = 1; i <= 9; i++) {
		if (grid.number(i, col) == num || grid.number(row, i) == num) {
			return true;
		}
	}
	// check block
	int rowAdd, colAdd;
	if (row % 3 != 0) { rowAdd = 1; } else { rowAdd = 0; }
	if (col % 3 != 0) { colAdd = 1; } else { colAdd = 0; }
	int rowBlock = (row / 3) + rowAdd;
	int colBlock = (col / 3) + colAdd;
	for (int i = 1; i <= 3; i++) { // row
		for (int j  = 1; j <= 3; j++) { // col
			int rowCheck = ((rowBlock - 1)* 3) + i;
			int colCheck = ((colBlock - 1)* 3) + j;
			if (grid.number(rowCheck, colCheck) == num) {
				return true;
			}
		}
	}
	// if no conflicts, return false
	return false;
}

/* Returns the amount of times the number n is penciled in
	in the row passed in. */
int numPencilsInRow(SudokuGrid& grid, int row, int n) {
	int numPencil = 0;
	for (int i = 1; i <= 9; i++) 
		if (grid.isPencilSet(row, i, n)) 
			numPencil++;
	return numPencil;
}

/* Returns the amount of times the number n is penciled in
	in the column passed in. */
int numPencilsInColumn(SudokuGrid& grid, int col, int n) {
	int numPencil = 0;
	for (int i = 1; i <= 9; i++) 
		if (grid.isPencilSet(i, col, n)) 
			numPencil++;
	return numPencil;
}

/* Returns the amount of times the number n is penciled in
	in the block that contains (row,col). */
int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n) {
	int numPencil = 0;	
	int rowAdd, colAdd;
	if (row % 3 != 0) { rowAdd = 1; } else { rowAdd = 0; }
	if (col % 3 != 0) { colAdd = 1; } else { colAdd = 0; }
	int rowBlock = (row / 3) + rowAdd;
	int colBlock = (col / 3) + colAdd;
	for (int i = 1; i <= 3; i++) { // row
		for (int j  = 1; j <= 3; j++) { // col
			int rowCheck = ((rowBlock - 1)* 3) + i;
			int colCheck = ((colBlock - 1)* 3) + j;
			if (grid.isPencilSet(rowCheck, colCheck, n)) {
				numPencil++;
			}
		}
	}
	return numPencil;
}

 //Algorithm for determining all possible pencil values 
void autoPencil(SudokuGrid& grid) {
	for (int r = 1; r <= 9; r++)
		for (int c = 1; c <= 9; c++)
			if (grid.number(r,c) == 0) {
				grid.setAllPencils(r,c);
				for (int n = 1; n <= 9; n++)
					if (conflictingNumber(grid,r,c,n))
						grid.clearPencil(r,c,n);
			}
}

// Algorithm for deducing cell values by searching for "naked singles." 
void deduce(SudokuGrid& grid) {
	bool changed;
	do { // repeat until no changes made
		autoPencil(grid);
		changed = false;
		for (int row = 1; row <= 9; row++)
			for (int col = 1; col <= 9; col++)
				for (int n = 1; n <= 9; n++)
					if (grid.isPencilSet(row, col, n) &&
							(numPencilsInRow(grid, row, n) == 1 ||
							numPencilsInColumn(grid, col, n) == 1 ||
							numPencilsInBlock(grid, row, col, n) == 1)) {
						grid.clearAllPencils(row, col);
						grid.setNumber(row,col,n);
						grid.setSolved(row,col);
						autoPencil(grid);
						changed = true;
						break;
					}
	} while(changed);
}

// Backtracking Sudoku solver 
bool solveSudoku(SudokuGrid& grid) {
	int row, col;
	if (!findUnassignedLocation(grid, row, col))
		return true; // puzzle filled, solution found!
	for (int num = 1; num <= 9; num++)
		if (!conflictingNumber(grid, row, col, num)) {
			grid.setNumber(row, col, num); // try next number
			if (solveSudoku(grid))
				return true;                 // solved!
			grid.setNumber(row, col, 0);   // not solved, clear number
		}
	return false; // not solved, back track
}

/* Prints out the Sudoku puzzle. */
void printSudoku(SudokuGrid& grid) {
	for (int row = 1; row <= 9; row++) {
		for (int col = 1; col <= 9; col++) {
			int num = grid.number(row, col);
			if (num == 0) {
				cout << ". ";
			} else {
				cout << num << " ";
			}
			if (col % 3 == 0 && col < 9) {
				cout << "| ";
			}
		}
		cout << "\n";
		if (row % 3 == 0 && row < 9) {
			cout << "------+-------+------\n";
		}
	}
}

int main(int argc, char *argv[]) {
  string puzzle;
  cin >> puzzle;
  if (puzzle.length() != 9*9 ||
      !all_of(puzzle.begin(), puzzle.end(),
	      [](char ch) {
		return ch == '.' || ('1' <= ch && ch <= '9');
	      })) {
    cerr << "bogus puzzle!" << endl; 
    exit(1);
  }

	//original
	SudokuGrid grid = SudokuGrid(puzzle);
	cout << "Original:\n";
	printSudoku(grid);

	//deduced
	//cout << "\nDeduced:\n";
	//deduce(grid);
	//printSudoku(grid);

	//solved
	solveSudoku(grid);
	cout << "\nSolved:\n";
	printSudoku(grid);
			  
  return 0;
}
