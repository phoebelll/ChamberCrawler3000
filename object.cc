#include "object.h"

Object::Object(char symbol) : symbol{symbol} {}

void Object::setPosition(Position pos) {
	this->pos = pos;
}

Position Object::getPosition() const {
	return pos;
}

char Object::getSymbol() const {
	return symbol;
}

Object::~Object() {}
