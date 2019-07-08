#ifndef _TILE_H_
#define _TILE_H_

#include <memory>
#include "position.h"
#include "subject.h"

class Character;
class Object;

class Tile : public Subject{
	Position posn;
	char symbol;

	bool hasChamber;

	bool occupied;
	std::shared_ptr<Object> object;
public:
	Tile(int row, int col, char symbol);
	char getSymbol() const;
	void setSymbol(char s);
	Position getPosn() const;

	bool isAssigned() const;
	void setAssigned();

	std::shared_ptr<Object> occupant() const;
	bool occupySpace(std::shared_ptr<Object> obj);
	void unoccupy();
	bool canBeOccupied(std::shared_ptr<Object> obj) const;

	void notifyObservers(std::string msg = "") const override;
	~Tile();
};

#endif
