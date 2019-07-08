#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>

struct Position {
	int x, y;
	Position(int x = 0, int y = 0) : x{x}, y{y} {}
};

std::ostream & operator<< (std::ostream & out, const Position &p);

#endif
