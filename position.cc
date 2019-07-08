#include "position.h"

std::ostream & operator<< (std::ostream & out, const Position &p) {
	out << '(' << p.x << ',' << p.y << ')';
	return out;
}
