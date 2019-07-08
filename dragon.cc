#include "dragon.h"
#include "dragonHoard.h"
using namespace std;

const int Dragon::baseHp = 150;
const int Dragon::baseAtk = 20;
const int Dragon::baseDef = 20;
const char Dragon::symbol = 'D';

Dragon::Dragon() 
	: Enemy{baseHp, baseAtk, baseDef, symbol} {}

Dragon::~Dragon() {}

void Dragon::setHoard (DragonHoard *dh){
	hoard = dh;
}

bool Dragon::detectHero(Position heroPosn) {
	return (Enemy::detectHero(heroPosn) || hoard->detectHero(heroPosn));
}

std::shared_ptr<Treasure> Dragon::dropGold() {
	hoard->setDragon(nullptr);
	return nullptr;
}

void Dragon::move(int x, int y) {}
