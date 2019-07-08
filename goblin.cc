#include "goblin.h"
#include "enemy.h"

const int Goblin::baseHp = 110;
const int Goblin::baseAtk = 15;
const int Goblin::baseDef = 20;
const char Goblin::symbol = 'G';

Goblin::Goblin() :
	Hero{baseHp, baseAtk, baseDef, symbol, baseHp} {}

Goblin::~Goblin(){}

int Goblin::attack(Enemy *e) {
	int damage = Hero::attack(e);
	if (e->isDead()) {
		gold += 5;
	}
	return damage;
}


int Goblin::beAttackedBy(Enemy *e) {
	int miss = rand() % 2;
	if(miss) {
		return 0;
	} else {
		int damage = calcDamage(e->getAtk(),def);
		if (e->getSymbol() == 'O') {	
			damage *= 1.5;
		} 
		hp -= damage;
		return damage;
	}
}



