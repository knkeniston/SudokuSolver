#include <iostream>
#include <string>
#include <sstream>
#include "Cell.h"

/* Kelly Kensiston, CS 355, Spring 2016
	This class represents a Cell object used by the SudokuGrid.
	It holds an integer value, and boolean values for being fixed
	and being solved. There are several public methods for gathering
	information from and modifying the cell. */

/* v = value of cell,
	f = is cell fixed
	s = is cell solved */	
Cell::Cell(int v, bool f, bool s) {
	setCellValue(v);
	fixed = f;
	solved = s;
}

// set value of cell to v
void Cell::setCellValue(int v) {
	val = v;
}

// returns whether or not the cell is fixed
bool Cell::isFixed() const {
	return fixed;
}

// returns value of the cell
int Cell::cellVal() const {
	return val;
}

// returns whether or not the cell is solved
bool Cell::isSolved() const {
	return solved;
}

// set the cell to solved
void Cell::setSolved(bool state) {
	solved = state;
}

// set all pencil values 1-9 in the cell
void Cell::setAllPencils(bool val) {
	for (int i = 0; i < 9; i++) {
		pencils[i] = val;
	}
}

// set pencil value of v to val
void Cell::setPencil(int v, bool val) {
	pencils[v] = val;
}

// returns whether there are any pencils set on the cell
bool Cell::anyPencilSet() const {
	for (int i = 0; i < 9; i++) {
		if (pencils[i] == true) { return true; }
	}
	return false;
}

// returns whether or not pencil v is set on cell
bool Cell::isPencilSet(int v) const {
	return pencils[v - 1];
}

