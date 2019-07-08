#ifndef _TREATURE_H_
#define _TREATURE_H_
#include "item.h"
#include <memory>

class Hero;

class Treasure : public Item {
	static char symbol;
protected:
	int value;
public:
	Treasure(int value, std::string name);
	virtual ~Treasure() = 0;
	int getValue();
	virtual bool bePickedUpBy(std::shared_ptr<Hero>);
};

#endif
