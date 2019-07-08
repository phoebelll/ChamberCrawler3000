#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class DragonHoard;

class Dragon : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

	DragonHoard *hoard;

public:
	Dragon();
	~Dragon();
	void setHoard (DragonHoard*);
	bool detectHero(Position heroPosn) override;
	std::shared_ptr<Treasure> dropGold() override;
	void move(int x, int y) override;
};

#endif
