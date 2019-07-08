#include "dragonHoard.h"
#include "dragon.h"
#include "hero.h"
#include <cstdlib>
#include <iostream>
using namespace std;

DragonHoard::DragonHoard() : Treasure{6, "Dragon Hoard"} {}

void DragonHoard::setDragon(Dragon *d) {
	dragon = d;
}

bool DragonHoard::bePickedUpBy(std::shared_ptr<Hero> h) {
	if (dragon == nullptr) {
		h->getTreasure(this);
		value = 0;
		return true;
	} else {
		return false;
	}
}

bool DragonHoard::detectHero(Position heroPosn) {
	if (abs(pos.x - heroPosn.x) <= 1 
		&& abs(pos.y - heroPosn.y) <= 1) {
		return true;
	} else {
		return false;
	}
}
