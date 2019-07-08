#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "enemy.h"

class Treasure;

class Human : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Human();
	~Human();
	std::shared_ptr<Treasure> dropGold() override;

};

#endif
