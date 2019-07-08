#include "human.h"
#include "normalGold.h"

const int Human::baseHp = 140;
const int Human::baseAtk = 20;
const int Human::baseDef = 20;
const char Human::symbol = 'H';

Human::Human():
	Enemy{baseHp, baseAtk, baseDef, symbol} {}


Human::~Human() {}


std::shared_ptr<Treasure> Human::dropGold() {
	return std::make_shared<NormalGold>();
}
