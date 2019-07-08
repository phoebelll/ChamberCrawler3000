#include "drow.h"
#include "potion.h"
using namespace std;

const int Drow::baseHp = 150;
const int Drow::baseAtk = 25;
const int Drow::baseDef = 15;
const char Drow::symbol = 'D';

Drow::Drow() :
	Hero{baseHp, baseAtk, baseDef, symbol, baseHp} {}

Drow::~Drow(){}

void Drow::usePotion(Potion *p) {
	char attribute = p->getAttribute();
	int value = 1.5 * p->getValue();
	if(attribute == 'H') {
		hp += value;
		if(hp >= maxHp) {
			hp = maxHp;
		}
		hp = max(0, hp);
	} else if (attribute == 'A') {
		atk = max(0, atk + value);
	} else if (attribute == 'D') {
		def = max(0, def + value);
	} 
}
