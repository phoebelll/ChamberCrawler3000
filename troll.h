#ifndef __TROLL_H__
#define __TROLL_H__
#include "hero.h"

class Troll : public Hero {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Troll();
	~Troll();
	int attack(Enemy *) override;
	void move(int x, int y) override;
};

#endif
