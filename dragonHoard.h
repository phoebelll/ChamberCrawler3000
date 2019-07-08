#ifndef _DRAGONHOARD_H_
#define _DRAGONHOARD_H_
#include "treasure.h"

class Dragon;

class DragonHoard : public Treasure {
	Dragon *dragon;
public:
	DragonHoard();
	~DragonHoard() = default;

	// used to intialize the dragon field. Will also be called with a nullptr 
	//   when the dragon is dead
	void setDragon(Dragon *);
	bool bePickedUpBy(std::shared_ptr<Hero>) override;
	bool detectHero(Position heroPosn);
};

#endif
