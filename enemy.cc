#include <iostream>
#include <cstdlib>
#include "enemy.h"
#include "hero.h"
#include "normalGold.h"
#include "smallGold.h"
using namespace std;

Enemy::Enemy(int hp, int atk, int def, char symbol) :
	Character{hp,atk,def,symbol} {}

Enemy::~Enemy(){}

bool Enemy::detectHero(Position heroPosn) {
	if (abs(pos.x - heroPosn.x) <= 1 
		&& abs(pos.y - heroPosn.y) <= 1) {
		return true;
	} else {
		return false;
	}
}

int Enemy::attack(Hero *h) {
	if (h) {
		return h->beAttackedBy(this);
	} else {
		return 0;
	}
}

int Enemy::beAttackedBy(Hero *h) {
	int damage = calcDamage(h->getAtk(),def);
	hp -= damage;
	return damage;
}

std::shared_ptr<Treasure> Enemy::dropGold() {
	bool isNormal = rand() % 2;
	if(isNormal) {
		return std::make_shared<NormalGold>();
	} else {
		return std::make_shared<SmallGold>();
	}
}

bool Enemy::operator<(Enemy &other) const {
	if (pos.x < other.pos.x) {
		return true;
	} else if (pos.x > other.pos.x) {
		return false;
	} else if (pos.y < other.pos.y) {
		return true;
	} else {
		return false;
	}
}

