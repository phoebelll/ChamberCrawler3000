#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "hero.h"

class Goblin : public Hero {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Goblin();
	~Goblin();
	int attack(Enemy *) override;
	int beAttackedBy(Enemy *) override;

};

#endif
