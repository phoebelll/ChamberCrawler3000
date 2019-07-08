#ifndef __SHADE_H__
#define __SHADE_H__
#include "hero.h"

class Shade : public Hero {

	static const int baseHp;
	static const int baseAtk;
	static const int baseDef;
	static const char symbol;

public:
	Shade();
	int getScore() const;
	~Shade();
};

#endif
