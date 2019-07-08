#include "merchant.h"
#include "hero.h"
#include "merchantGold.h"
using namespace std;

const int Merchant::baseHp = 30;
const int Merchant::baseAtk = 70;
const int Merchant::baseDef = 5;
const char Merchant::symbol = 'M';
bool Merchant::isHostile = false;

Merchant::Merchant() :
	Enemy{baseHp, baseAtk, baseDef, symbol} {}

Merchant::~Merchant() {}

int Merchant::beAttackedBy(Hero *h) {
	isHostile = true;
	return Enemy::beAttackedBy(h);
}

bool Merchant::detectHero(Position heroPosn){
	if(isHostile) {
		return Enemy::detectHero(heroPosn);
	} else {
		return false;
	}
}

std::shared_ptr<Treasure> Merchant::dropGold(){
	return std::make_shared<MerchantGold>();
}
