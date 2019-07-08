#include "item.h"

Item::Item(char symbol, std::string name) : Object{symbol}, name{name} {}

std::string Item::getName() const {
	return name;
}

Item::~Item() {}
