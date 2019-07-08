#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>
#include <vector>
#include <string>
#include "observer.h"

class TextDisplay: public Observer {
	const int rows, cols;
	std::vector<std::vector<char>> boardDisplay;
	std::string raceAndGold, hp, atk, def, act;
public:
	TextDisplay(int rows = 25, int cols = 79);
	void notify(int row, int col, char symbol) override;
	void notify(std::shared_ptr<Hero> h, int floor) override;
	void notify(std::string action) override;
	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
