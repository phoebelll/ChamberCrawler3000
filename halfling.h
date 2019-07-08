#ifndef __HALFlING_H__
#define __HALFlING_H__
#include "enemy.h"

class Halfling : public Enemy {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Halfling();
	~Halfling();
	int beAttackedBy (Hero *) override;
};

#endif
