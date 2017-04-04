#ifndef CELL_H
#define CELL_H

#include <array>
#include <bitset>
#include <string>

class Cell {
	private:
		std::bitset<9> pencils; // value 0..8 represent pencils 1..9
		int val;
		bool fixed;
		bool solved;
	public:
		Cell(int v = 0, bool fixed=false, bool solved=false);
		int cellVal() const;
		void setCellValue(int v);
		bool isFixed() const;
		bool isSolved() const;
		void setSolved(bool state);
		bool isPencilSet(int v) const;
		bool anyPencilSet() const;
		void setPencil(int v, bool val);
		void setAllPencils(bool val);

};

#endif
