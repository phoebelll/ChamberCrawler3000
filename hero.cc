#include <iostream>
#include <cstdlib>
#include "hero.h"
#include "potion.h"
#include "treasure.h"
#include "enemy.h"
using namespace std;

Hero::Hero(int hp, int atk, int def, char symbol, int maxHp) : 
		Character{hp,atk,def,symbol}
		, maxHp{maxHp} 
		, baseAtk{atk}
		, baseDef{def}
	{}

Hero::~Hero() {}

int Hero::getScore() const {
	return gold;
}

int Hero::getGold() const {
	return gold;
}

void Hero::resetStats() {
	atk = baseAtk;
	def = baseDef;
}

int Hero::attack(Enemy *e) {
	if (e) {
		return e->beAttackedBy(this);
	} else {
		return 0;
	}
}


int Hero::beAttackedBy(Enemy *e) {
	int miss = rand() % 2;
	if (miss) {
		return 0;
	} else {
		int damage = calcDamage(e->getAtk(), def);
		hp -= damage;
		return damage;
	}
}


void Hero::usePotion(Potion *p) {
	char attribute = p->getAttribute();
	int value = p->getValue();
	if(attribute == 'H') {
		hp += value;
		if(hp >= maxHp){
			hp = maxHp;
		}
		hp = max(0,hp);
	} else if (attribute == 'A') {
		 atk = max(0,atk + value);
	} else if (attribute == 'D') {
		def = max(0,def + value);
	}
}

void Hero::getTreasure(Treasure *t) {
	int value = t->getValue();
	gold += value;
}
