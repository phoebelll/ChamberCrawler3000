#include <iostream>
#include "grid.h"
#include "textdisplay.h"
#include "tile.h"
#include "object.h"
using namespace std;

Grid::Grid(int rows, int cols) 
		: rows{rows}, cols{cols}, td{make_shared<TextDisplay>()}
	{
		for (int i = 0; i < rows; ++i) {
			theGrid.emplace_back(vector<shared_ptr<Tile>>(cols));
		}
}

Grid::~Grid() {}

std::shared_ptr<TextDisplay> Grid::getDisplay() {
	return td;
}

bool Grid::isStair(int row, int col) const {
	if (theGrid[row][col] != nullptr) {
		return '\\' == theGrid[row][col]->getSymbol();
	}
	return false;
}

void Grid::setTile(int row, int col, char symbol) {
	if (theGrid[row][col] == nullptr) {
		theGrid[row][col] = make_shared<Tile>(row, col, symbol);
		theGrid[row][col]->attach(td);
	} else {
		theGrid[row][col]->setSymbol(symbol);
	}
	
	theGrid[row][col]->notifyObservers();
}

bool Grid::isAssigned(int row, int col) const {
	if (theGrid[row][col] == nullptr) {
		return true;
	}
	return theGrid[row][col]->isAssigned();
}

void Grid::setAssigned(int row, int col) const {
	if (theGrid[row][col] != nullptr) {
		theGrid[row][col]->setAssigned();
	}
}

Position Grid::nextUassignedFloorTile(int r, int c) const {
	while (r < rows) {
		while (c < cols) {
			if (!isAssigned(r,c)) {
				return Position{r,c};
			}
			++c;
		}
		c = 0;
		++r;
	}

	return Position{-1,-1};
}

std::shared_ptr<Object> Grid::occupant(int row, int col) const {
	if (theGrid[row][col] != nullptr) {
		return theGrid[row][col]->occupant();
	} else {
		return nullptr;
	}
}

bool Grid::occupySpace(int row, int col, std::shared_ptr<Object> obj) const {
	if (theGrid[row][col] != nullptr) {
		return theGrid[row][col]->occupySpace(obj);	
	}
	return false;
}

void Grid::unoccupy(int row, int col) const {
	if (theGrid[row][col] != nullptr) {
		return theGrid[row][col]->unoccupy();	
	}
}

bool Grid::canBeOccupied(int row, int col, std::shared_ptr<Object> obj) const {
	if (theGrid[row][col] != nullptr) {
		return theGrid[row][col]->canBeOccupied(obj);	
	}

	return false;
}

ostream &operator<<(ostream &out, const Grid &g) {
	out << *(g.td);
	return out;
}
