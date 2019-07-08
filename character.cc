#include <iostream>
#include <cmath>
#include "character.h"

Character::Character(int hp, int atk, int def, char symbol) 
		: Object{symbol}
		, hp{hp}
		, atk{atk}
		, def{def} 
	{}

Character::~Character() {}

int Character::getHp() const {
	return hp;
}

int Character::getAtk() const {
	return atk;
}

int Character::getDef() const {
	return def;
}

bool Character::isDead() const {
	return hp <= 0;
}

void Character::move(int x, int y){
	pos.x += x;
	pos.y += y;
}

int Character::calcDamage(int attack, int defence) const {
	return static_cast<int>(ceil((100.0 / (100.0 + defence)) * attack));
}






