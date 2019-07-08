#include <cstdlib>
#include "halfling.h"
#include "hero.h"

const int Halfling::baseHp = 100;
const int Halfling::baseAtk = 15;
const int Halfling::baseDef = 20;
const char Halfling::symbol = 'L';


Halfling::Halfling():
	Enemy{baseHp, baseAtk, baseDef, symbol} {}

Halfling::~Halfling(){}

int Halfling::beAttackedBy(Hero *h) {
	int miss = rand() % 2;
	if(!miss) {
		int damage = calcDamage(h->getAtk(), def);
		hp -= damage;
		return damage;
	} else {
		return 0;
	}
}
