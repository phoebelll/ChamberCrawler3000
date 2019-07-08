#include <climits>
#include "vampire.h"
#include "enemy.h"

const int Vampire::baseHp = 50;
const int Vampire::baseAtk = 25;
const int Vampire::baseDef = 25;
const char Vampire::symbol = 'V';

Vampire::Vampire() :
	Hero{baseHp, baseAtk, baseDef, symbol, INT_MAX} {}

Vampire::~Vampire(){}

int Vampire::attack(Enemy *e) {
	int damage = e->beAttackedBy(this);
	if (damage) {
		if(e->getSymbol() == 'W') {
			hp -= 5;
		} else {
			hp += 5;
	  	}
	}
	return damage;
}

