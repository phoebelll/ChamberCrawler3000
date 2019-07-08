#ifndef __DWARF_H__
#define __DWARF_H__
#include "enemy.h"

class Dwarf : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Dwarf();
	~Dwarf();
};

#endif
