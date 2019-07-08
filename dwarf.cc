#include "dwarf.h"

const int Dwarf::baseHp = 100;
const int Dwarf::baseAtk = 20;
const int Dwarf::baseDef = 30;
const char Dwarf::symbol = 'W';

Dwarf::Dwarf():
	Enemy{baseHp, baseAtk, baseDef, symbol} {}

Dwarf::~Dwarf() {}

