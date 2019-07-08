#ifndef _CHAMBER_H_
#define _CHAMBER_H_

#include <vector>
#include <iostream>

struct Position;

class Chamber {
	std::vector<Position> posns;
public:
	Chamber() = default;
	Position extractIthPosn(int i);
	int getNumOfPosns() const;
	void addPosn(const Position p);
	int indexOfAdjacentPosns(std::vector<int> &indices) const;

	~Chamber() = default;

	friend std::ostream &operator<<(std::ostream &out, const Chamber &c);
};

#endif
