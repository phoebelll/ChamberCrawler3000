#ifndef __ORC_H__
#define __ORC_H__
#include "enemy.h"

class Orc : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Orc();
	~Orc();
};

#endif
