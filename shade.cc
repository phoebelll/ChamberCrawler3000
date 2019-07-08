#include "shade.h"

const int Shade::baseHp = 125;
const int Shade::baseAtk = 25;
const int Shade::baseDef = 25;
const char Shade::symbol = 'S';

Shade::Shade() :
	Hero{baseHp, baseAtk, baseDef, symbol, baseHp} {}

int Shade::getScore() const {
	return gold * 1.5;
}

Shade::~Shade() {}
