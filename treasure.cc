#include "treasure.h"
#include "hero.h"
#include <iostream>

char Treasure::symbol = 'G';

Treasure::Treasure(int value, std::string name) 
		: Item{symbol, name}
		, value{value} 
	{}

Treasure::~Treasure() {}

int Treasure::getValue() {
	return value;
}

bool Treasure::bePickedUpBy(std::shared_ptr<Hero> h) {
	h->getTreasure(this);
	value = 0;
	return true;
}
