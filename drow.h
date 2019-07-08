#ifndef __DROW_H__
#define __DROW_H__
#include "hero.h"

class Drow : public Hero {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Drow();
	~Drow();
	void usePotion(Potion *) override;
	
};

#endif
