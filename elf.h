#ifndef __ELF_H__
#define __ELF_H__
#include "enemy.h"

class Elf : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Elf();
	~Elf();
	int attack(Hero *) override;
};

#endif
