#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "position.h"

class Object {
protected:
	Position pos;
	char symbol;
public:
	Object(char symbol);
	void setPosition(Position pos);
	Position getPosition() const;
	char getSymbol() const;
	virtual ~Object() = 0;
};

#endif
