#include "potion.h"
#include "hero.h"

char Potion::symbol = 'P';

Potion::Potion(int value, char attribute, std::string name) 
		: Item{symbol, name}
		, value{value}
		, attribute{attribute} 
	{}
	
Potion::~Potion() {}

int Potion::getValue() const {
	return value;
}

char Potion::getAttribute() const {
	return attribute;
}

bool Potion::beUsedBy(std::shared_ptr<Hero> h) {
	h->usePotion(this);
	value = 0;
	return true;
}
