#ifndef __HERO_H__
#define __HERO_H__
#include "character.h"
#include <memory>
#include <cmath>

class Enemy;
class Potion;
class Treasure;


class Hero : public Character {
	const int baseAtk;
	const int baseDef;
protected:
	int gold = 0;
	const int maxHp;

public:
	Hero(int hp, int atk, int def, char symbol, int maxHp);
	virtual ~Hero() = 0;

	int getGold() const;
	void resetStats();
	virtual int getScore() const;
	virtual int attack(Enemy *);
	virtual int beAttackedBy(Enemy *);

	virtual void usePotion(Potion *);
	virtual void getTreasure(Treasure *);

};

#endif
