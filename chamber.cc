#include "chamber.h"
#include "tile.h"
#include "position.h"
using namespace std;

Position Chamber::extractIthPosn(int i){
	Position temp = posns[i];
	posns.erase(posns.begin() + i);
	return temp;
}

int Chamber::getNumOfPosns() const {
	return posns.size();
}

void Chamber::addPosn(const Position p) {
	posns.push_back(p);
}

ostream &operator<<(ostream &out, const Chamber &c) {
	for (int i = 0; i < c.posns.size(); ++i) {
		out << c.posns[i] << ' ';
	}
	return out;
}

int abs(int n) {
	if (n < 0) {
		return n * -1;
	} else {
		return n;
	}
}

bool isAdjacent (const Position & p1, const Position & p2) {
	int xDistance = p1.x - p2.x;
	int yDistance = p1.y - p2.y;

	if (abs(xDistance) <= 1 && abs(yDistance) <= 1) {
		return true;
	} else {
		return false;
	}
}

int Chamber::indexOfAdjacentPosns(vector<int> &indices) const {
	int count = 0;

	for (int i = 0; i < posns.size() - 1; ++i) {
		for (int j = i + 1; j < posns.size(); ++j) {
			if (isAdjacent(posns[i], posns[j])) {
				indices.push_back(i);
				indices.push_back(j);
				indices.push_back(j);
				indices.push_back(i);
				count += 2;
			}
		}
	}

	return count;
}
