#ifndef _POTION_H_
#define _POTION_H_
#include "item.h"
#include <memory>

class Hero;

class Potion : public Item {
	static char symbol;
protected:
	int value;
	// 'H' for hp, A' for attack, 'D' for defence
	char attribute;
public:
	Potion(int val, char attribute, std::string name);
	int getValue() const;
	char getAttribute() const;
	virtual bool beUsedBy(std::shared_ptr<Hero>);
	virtual ~Potion() = 0;
};

#endif
