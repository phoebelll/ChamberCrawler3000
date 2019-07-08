#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "object.h"

class Character : public Object{
protected:
	int hp, atk, def;

public:
	Character(int hp, int atk, int def, char symbol);
	virtual ~Character() = 0;
	int getHp() const;
	int getAtk() const;
	int getDef() const;
	bool isDead() const;
	int calcDamage(int attack, int defence) const;
	virtual void move(int x, int y);

};

#endif
