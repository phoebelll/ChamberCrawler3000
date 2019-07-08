#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "character.h"
#include <memory>
#include <vector>

class Treasure;
class Hero;

class Enemy : public Character {
public:
	Enemy(int hp, int atk, int def, char symbol);
	virtual ~Enemy() = 0;
	virtual bool detectHero(Position heroPosn);
	
	virtual int attack(Hero *);
	virtual int beAttackedBy(Hero *);
	virtual std::shared_ptr<Treasure> dropGold();
	bool operator< (Enemy &other) const;
};

#endif
