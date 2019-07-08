#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "hero.h"

class Vampire : public Hero {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Vampire();
	~Vampire();
	int attack(Enemy *) override;
};

#endif
