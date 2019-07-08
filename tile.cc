#include "tile.h"
#include "observer.h"
#include "character.h"
#include "object.h"
#include "hero.h"
#include "enemy.h"
#include <iostream>

Tile::Tile (int row, int col, char symbol) 
		: posn{row, col}
		, symbol{symbol} 
		, hasChamber{(symbol == '.' ? false : true)}
		, occupied{symbol == '-' || symbol == '|' || symbol =='\\'}
		, object{nullptr}
	{}

char Tile::getSymbol() const {
	if (occupied && symbol != '-' && symbol != '|' && symbol !='\\') {
		if (std::dynamic_pointer_cast<Hero>(object)) {
			return '@';
		} else {
			return object->getSymbol();
		}
	} else {
		return symbol;
	}
}

void Tile::setSymbol(char s) {
	symbol = s;
}

Position Tile::getPosn() const {
	return posn;
}

bool Tile::isAssigned() const {
	return hasChamber;
}

void Tile::setAssigned() {
	hasChamber = true;
}

std::shared_ptr<Object> Tile::occupant() const {
	return object;
}

bool Tile::occupySpace(std::shared_ptr<Object> obj) {
	if (occupied) {
		return false;
	}

	/*char objSymb = obj->getSymbol();

	if (symbol != '.' && (std::dynamic_pointer_cast<Enemy>(obj))) {
		return false;
	}*/

	object = obj;
	occupied = true;
	notifyObservers();
	return true;
}

void Tile::unoccupy() {
	// valid only if not a wall tile
	if (symbol != '-' && symbol != '|' && symbol !='\\') {
		occupied = false;
		object = nullptr;
	}
	notifyObservers();
}

bool Tile::canBeOccupied(std::shared_ptr<Object> obj) const {
	if (symbol != '.' && (std::dynamic_pointer_cast<Enemy>(obj))) {
		return false;
	} else {
		return !occupied;
	}
}

void Tile::notifyObservers(std::string msg) const {
	for (auto & ob : observers) {
		ob->notify(posn.x, posn.y, getSymbol());
	}
}

Tile::~Tile() {}
