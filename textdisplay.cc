#include <iostream>
#include <sstream>
#include "textdisplay.h"
#include "hero.h"
using namespace std;

// initialize theDisplay to a nxn 2d vector filled with '_'
TextDisplay::TextDisplay(int rows, int cols) 
		: rows{rows}
		, cols{cols}
		, boardDisplay{rows, vector<char>(cols, ' ')}
	{}

void TextDisplay::notify(int row, int col, char symbol) {
	boardDisplay[row][col] = symbol;
}

void TextDisplay::notify(std::shared_ptr<Hero> h, int floor) {
	ostringstream oss;
	oss << "Race: ";
	char race = h->getSymbol();

	switch(race) {
		case 'S':
			oss << "Shade";
			break;
		case 'D':
			oss << "Drow";
			break;
		case 'V':
			oss << "Vampire";
			break;
		case 'G':
			oss << "Goblin";
			break;
		case 'T':
			oss << "Troll";
	}

	oss << " Gold: " << h->getGold();
	oss << string(cols - oss.str().size() - 10, ' ') << "Floor: " << floor;
	raceAndGold = oss.str();

	hp = "HP: " + to_string(h->getHp());
	atk = "Atk: " + to_string(h->getAtk());
	def = "Def: " + to_string(h->getDef());
}

void TextDisplay::notify(string action) {
	act = "Action: " + action;
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (auto & row : td.boardDisplay) {
		for (auto & symbol : row) {
			out << symbol;
		}
		out << endl;
	}
	out << td.raceAndGold << endl << td.hp << endl << td.atk << endl 
		<< td.def << endl << td.act << endl;
	return out;
}
