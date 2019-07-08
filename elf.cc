#include "elf.h"
#include "hero.h"

const int Elf::baseHp = 140;
const int Elf::baseAtk = 30;
const int Elf::baseDef = 10;
const char Elf::symbol = 'E';

Elf::Elf():
	Enemy{baseHp, baseAtk, baseDef, symbol} {}

Elf::~Elf() {}

int Elf::attack(Hero *h) {
	int damage = h->beAttackedBy(this);
	if(h->getSymbol() != 'D') {
		damage += h->beAttackedBy(this);
	}
	return damage;
}
