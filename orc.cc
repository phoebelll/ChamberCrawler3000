#include "orc.h"

const int Orc::baseHp = 180;
const int Orc::baseAtk = 30;
const int Orc::baseDef = 25;
const char Orc::symbol = 'O';

Orc::Orc():
	Enemy{baseHp, baseAtk, baseDef, symbol} {}

Orc::~Orc() {}


