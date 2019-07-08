#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "enemy.h"

class Merchant : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;
	static bool isHostile;

public:
	Merchant();
	~Merchant();
	int beAttackedBy(Hero *) override;
	bool detectHero(Position heroPosn) override;
	std::shared_ptr<Treasure> dropGold() override;
};

#endif
