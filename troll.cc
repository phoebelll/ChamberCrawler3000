#include "troll.h"
#include "enemy.h"
using namespace std;

const int Troll::baseHp = 120;
const int Troll::baseAtk = 25;
const int Troll::baseDef = 15;
const char Troll::symbol = 'T';

Troll::Troll() :
	Hero{baseHp, baseAtk, baseDef, symbol, baseHp} {}

Troll::~Troll(){}


int Troll::attack(Enemy *e){
	int damage = Hero::attack(e);
	if(hp > 0){
		hp = min(maxHp, hp + 5);
	}
	return damage;
}

void Troll::move(int x, int y) {
	Hero::move(x,y);
	hp = min(maxHp, hp + 5);
}
