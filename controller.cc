#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "controller.h"
#include "textdisplay.h"
#include "object.h"
#include "grid.h"
#include "chamber.h"
#include "treasure.h"
#include "potion.h"
#include "merchantGold.h"
#include "boostatk.h"
#include "smallGold.h"
#include "normalGold.h"
#include "boostdef.h"
#include "poisonhealth.h"
#include "woundatk.h"
#include "dragonHoard.h"
#include "wounddef.h"
#include "item.h"
#include "restorehealth.h"
#include "character.h"
#include "dwarf.h"
#include "goblin.h"
#include "human.h"
#include "shade.h"
#include "dragon.h"
#include "elf.h"
#include "halfling.h"
#include "merchant.h"
#include "troll.h"
#include "drow.h"
#include "enemy.h"
#include "hero.h"
#include "orc.h"
#include "vampire.h"
using namespace std;

Controller::Controller(ostream &out, istream &in) 
		: out{out}
		, in{in}
	{}

shared_ptr<Enemy> constructEnemyFromSymbol(char symbol) {
	switch (symbol) {
		case 'H':
			return make_shared<Human>();
		case 'W':
			return make_shared<Dwarf>();
		case 'E':
			return make_shared<Elf>();
		case 'O':
			return make_shared<Orc>();
		case 'M':
			return make_shared<Merchant>();
		case 'D':
			return make_shared<Dragon>();
		case 'L':
			return make_shared<Halfling>();
		default :
			return nullptr;
	}
}

shared_ptr<Hero> constructHeroFromCommand(char c) {
	switch (c) {
		case 's':
			return make_shared<Shade>();
		case 'd':
			return make_shared<Drow>();
		case 'v':
			return make_shared<Vampire>();
		case 'g':
			return make_shared<Goblin>();
		case 't':
			return make_shared<Troll>();
		default :
			return nullptr;
	}
}

shared_ptr<Potion> constructPotionFromNumber(char num) {
	switch(num) {
		case '0':
			return make_shared<RestoreHealth>();
		case '1':
			return make_shared<BoostAtk>();
		case '2':
			return make_shared<BoostDef>();
		case '3':
			return make_shared<PoisonHealth>();
		case '4':
			return make_shared<WoundAtk>();
		case '5':
			return make_shared<WoundDef>();
		default :
			return nullptr;
	}
}

shared_ptr<Treasure> constructTreasureFromNumber(char num) {
	switch(num) {
		case '6':
			return make_shared<NormalGold>();
		case '7': 
			return make_shared<SmallGold>();
		case '8':
			return make_shared<MerchantGold>();
		case '9':
			return make_shared<DragonHoard>();
		default :
			return nullptr;
	}
}

void Controller::readMap(std::string fileName) {
	ifstream file{fileName};
	int row = 0;
	int col = 0;
	string line;

	if (floorPopulated) {
		for (int i = 1; i < floor; ++i) {
			for (int j = 0; j < numRow; ++j) {
				getline(file, line);
			}
		}
	}
	

	while (row < numRow) {
		getline(file, line);
		istringstream iss{line};
		char c;
		while (col < numCol) {
			iss >> noskipws >> c;
			Position curPos {row, col};
			if (c == ' ') {
				++col;
				continue;
			} else if ('A' <= c && c <= 'Z') {
				shared_ptr<Enemy> e = constructEnemyFromSymbol(c);
				e->setPosition(curPos);
				enemies.push_back(e);
				grid->setTile(row, col, '.');

				if (c == 'D') {
					dragons.push_back(dynamic_pointer_cast<Dragon>(e));
				}
			} else if ('0' <= c && c <= '5') {
				shared_ptr<Potion> p = constructPotionFromNumber(c);
				p->setPosition(curPos);
				potions.push_back(p);
				grid->setTile(row, col, '.');
			} else if ('6' <= c && c<= '9') {
				shared_ptr<Treasure> t = constructTreasureFromNumber(c);
				t->setPosition(curPos);
				treasures.push_back(t);
				grid->setTile(row, col, '.');

				if (c == '9') {
					hoards.push_back(dynamic_pointer_cast<DragonHoard>(t));
				}
			} else if (c == '@') {
				floorPopulated = true;
				hero->setPosition(curPos);
				grid->setTile(row, col, '.');
			} else if (c == '\\') {
				stairPosn.x = row;
				stairPosn.y = col;
				grid->setTile(row, col, '\\');
			} else {
				grid->setTile(row, col, c);
			}
			++col;
		}
		col = 0;
		++row;
	}
}

void populateChamber(shared_ptr<Chamber> chamber, Position posn, shared_ptr<Grid> g) {
	if (posn.x < 0 || posn.y < 0) {
		return;
	}

	chamber->addPosn(posn);
	g->setAssigned(posn.x, posn.y);

	if (!g->isAssigned(posn.x - 1, posn.y)) {
		populateChamber(chamber, Position{posn.x - 1, posn.y}, g);
	}
	if (!g->isAssigned(posn.x + 1, posn.y)) {
		populateChamber(chamber, Position{posn.x + 1, posn.y}, g);
	}
	if (!g->isAssigned(posn.x, posn.y - 1)) {
		populateChamber(chamber, Position{posn.x, posn.y - 1}, g);
	}
	if (!g->isAssigned(posn.x, posn.y + 1)) {
		populateChamber(chamber, Position{posn.x, posn.y + 1}, g);
	}
}

void Controller::initChambers() {
	Position curUnassigned {0,0};

	for (int i = 0; i < numChamber; ++i) {
		shared_ptr<Chamber> chamber = make_shared<Chamber>();
		curUnassigned = grid->nextUassignedFloorTile(curUnassigned.x, 
													 curUnassigned.y);
		populateChamber(chamber, curUnassigned, grid);
		chambers.push_back(chamber);
	}
}

void Controller::printGrid(std::ostream & out) const {
	out << *grid << endl;
}

void Controller::printChamber(std::ostream & out) const {
	for (int i = 0; i < numChamber; ++i) {
		out << *chambers[i] << endl;
	}
}

// returns a random position from a random chamber, each chamber have the same
//   probability regardless of size. 
// requires: chambers is not empty
//           at least one of the chambers is not empty
Position Controller::randomPosnFromChamber(int choosenChamber) {
	if (choosenChamber == -1) {
		choosenChamber = rand() % numChamber;
	}
	shared_ptr<Chamber> curChamber = chambers[choosenChamber];
	int size = curChamber->getNumOfPosns();
	int randomIndex = rand() % size;
	Position posn = curChamber->extractIthPosn(randomIndex);

	if (size == 1) {
		chambers.erase(chambers.begin() + choosenChamber);
		--numChamber;
	}

	return posn;
}

bool Controller::randomAdjacentPosnsFromChamber(vector<Position> & v) {
	int randomChamber = rand() % numChamber;
	shared_ptr<Chamber> curChamber = chambers[randomChamber];
	vector<int> indices;
	int numPairs = curChamber->indexOfAdjacentPosns(indices);
	
	if (numPairs == 0) {
		int temp = randomChamber;
		while(numPairs == 0) {
			++randomChamber;

			if (randomChamber >= numChamber) {
				randomChamber = 0;
			}

			// after the going through all available chambers and none have
			//   adjacent Positions, return false
			if (randomChamber == temp) {
				return false;
			}

			curChamber = chambers[randomChamber];
			numPairs = curChamber->indexOfAdjacentPosns(indices);
		}
	}

	int randomPair = rand() % numPairs;

	int index1 = indices[randomPair * 2];
	int index2 = indices[randomPair * 2 + 1];

	// extract the Position with the larger index before the Position 
	//   with the smaller index because extracting an element from an array
	//   changes the indices of later elements
	if (index1 > index2) {
		v.push_back(curChamber->extractIthPosn(index1));
		v.push_back(curChamber->extractIthPosn(index2));
	} else {
		v.push_back(curChamber->extractIthPosn(index2));
		v.push_back(curChamber->extractIthPosn(index1));
	}
	
	return true;
}

void Controller::spawnAll() {
	// player position
	int playerChamber = rand() % numChamber;
	Position randomPosn = randomPosnFromChamber(playerChamber);
	hero->setPosition(randomPosn);

	// stairway position, cannot be in the same chamber as player
	int stairChamber = rand() % numChamber;
	while (stairChamber == playerChamber) {
		stairChamber = rand() % numChamber;
	}
	stairPosn = randomPosnFromChamber(stairChamber);
	grid->setTile(stairPosn.x, stairPosn.y, '\\');

	// potions
	for (int i = 0; i < numPotion; ++i) {
		const int typesOfPotion = 6;

		char randomPotion = rand() % typesOfPotion + '0';
		shared_ptr<Potion> p = constructPotionFromNumber(randomPotion);

		randomPosn = randomPosnFromChamber();
		p->setPosition(randomPosn);

		potions.push_back(p);
	}

	// gold
	bool noAdjacentPosns = false; // true if no adjacent tiles in any chamber
	for (int i = 0; i < numTreasure; ++i) {
		// spawn rate of gold is 5/8 chance of normal, 1/4 small hoard, 1/8 
		//   dragon hoard. So, randomly generate a number from 1 to 8, 1-5 
		//   spawn normal, 6-7 spawn small, 8 spawn dragon hoard
		int outcome;
		if (noAdjacentPosns) {
			// if no adjacent tiles left, cannot spawn dragon hoard
			outcome = rand() % 7 + 1;
		} else {
			outcome = rand() % 8 + 1;
		}
		
		if (outcome != 8) {
			shared_ptr<Treasure> t;

			if (outcome <= 5) {
				t = make_shared<NormalGold>();
			} else {
				t = make_shared<SmallGold>();
			}

			randomPosn = randomPosnFromChamber();
			t->setPosition(randomPosn);

			treasures.push_back(t);
		} else {
			auto dh = make_shared<DragonHoard>();

			vector<Position> posns;
			if (!randomAdjacentPosnsFromChamber(posns)) {
				--i;
				noAdjacentPosns = true;
				continue;
			}

			dh->setPosition(posns[0]);

			// if it's dragonHoard, spawn a dragon in an adjacent tile
			shared_ptr<Dragon> d = make_shared<Dragon>();
			d->setPosition(posns[1]);
			enemies.push_back(d);
			dh->setDragon(d.get());
			d->setHoard(dh.get());

			treasures.push_back(dh);
		}
	}

	// enemies
	for (int i = 0; i < numEnemy; ++i) {
		// spawn rate of enemies is 2/9 chance of Human, 3/18 Dwarf, 5/18
		//   Halfling, 1/9 Elf, 1/9 Orc, 1/9 Merchant. So, randomly generate 
		//   a number from 1 to 18:
		// 		1-4 spawn Human
		// 		5-7 spawn Dwarf
		//		8-12 spawn Halfling
		//		13-14 spawn Elf
		//		15-16 spawn Orc
		//		17-18 spawn Merchant
		shared_ptr<Enemy> e;
		int outcome = rand() % 18 + 1;

		if (outcome <= 4) {
			e = make_shared<Human>();
		} else if (outcome <= 7) {
			e = make_shared<Dwarf>();
		} else if (outcome <= 12) {
			e = make_shared<Halfling>();
		} else if (outcome <= 14) {
			e = make_shared<Elf>();
		} else if (outcome <= 16) {
			e = make_shared<Orc>();
		} else {
			e = make_shared<Merchant>();
		}
		
		randomPosn = randomPosnFromChamber();
		e->setPosition(randomPosn);

		enemies.push_back(e);
	}
}

void placeOnGrid(shared_ptr<Object> obj, shared_ptr<Grid> g) {
	Position curPos = obj->getPosition();
	g->occupySpace(curPos.x, curPos.y, obj);
}

void Controller::setUp() {
	placeOnGrid(hero, grid);

	for (auto p : potions) {
		placeOnGrid(p, grid);
	}

	for (auto t : treasures) {
		placeOnGrid(t, grid);
	}

	for (auto e : enemies) {
		placeOnGrid(e, grid);
	}
}

Position getDirectionPos(string dir) {
	if (dir == "no") {
		return Position{-1,0};
	} else if (dir == "so") {
		return Position{1,0};
	} else if (dir == "ea") {
		return Position{0,1};
	} else if (dir == "we") {
		return Position{0,-1};
	} else if (dir == "ne") {
		return Position{-1,1};
	} else if (dir == "nw") {
		return Position{-1,-1};
	} else if (dir == "se") {
		return Position{1,1};
	} else if (dir == "sw") {
		return Position{1,-1};
	} else {
		return Position{0,0};
	}
}

string posToString(Position &pos) {
	ostringstream output;

	if (pos.x == -1) {
		output << "North";
	} else if (pos.x == 1) {
		output << "South";
	}

	if (pos.x != 0 && pos.y != 0) {
		output << ' ';
	}

	if (pos.y == 1) {
		output << "East";
	} else if (pos.y == -1) {
		output << "West";
	}

	return output.str();
}

// returns any action, can throw InvalidCommend
string Controller::evaluateCommend(string cmd) {
	Position movePosn;
	Position heroPosn = hero->getPosition();
	ostringstream oss;
	if (cmd[0] == 'a') {
		movePosn = getDirectionPos(cmd.substr(1));
		if (movePosn.x != 0 || movePosn.y != 0) {
			Position destination {heroPosn.x + movePosn.x
								, heroPosn.y + movePosn.y};
			shared_ptr<Enemy> e = (dynamic_pointer_cast<Enemy>(grid->
				occupant(destination.x, destination.y)));
			if (e != nullptr) {
				int damage = hero->attack(e.get());
				oss << "PC deals " << damage << " damage to " << e->getSymbol() 
					<< " (" << e->getHp() << " HP). ";

				if (e->isDead()) {
					Position temp = e->getPosition();
					grid->unoccupy(temp.x, temp.y);

					for (int i = 0; i < enemies.size(); ++i) {
						if (e == enemies[i]) {
							enemies.erase(enemies.begin() + i);
							break;
						}
					}

					shared_ptr<Treasure> gold = e->dropGold();
					if (e->getSymbol() == 'D') {
						// do nothing
					} else if (e->getSymbol() == 'H') {
						grid->occupySpace(destination.x, destination.y, gold);
						treasures.push_back(gold);
						gold = e->dropGold();

						vector<Position> posns;
						availablePosns(destination, posns, gold);
						if (posns.size() > 0) {
							Position tempPosn = posns[rand() % posns.size()];
							grid->occupySpace(destination.x + tempPosn.x, 
								destination.y + tempPosn.y, gold);
							treasures.push_back(gold);
						}
					} else if (e->getSymbol() == 'M') {
						grid->occupySpace(destination.x, destination.y, gold);
						treasures.push_back(gold);
					} else {
						gold->bePickedUpBy(hero);
					}
					
					if (e->getSymbol() == 'H') {
						oss << "Dropped two " << gold->getName() << "s. ";
					} else if (e->getSymbol() != 'D') {
						oss << "Dropped a " << gold->getName() << ". ";
					}

					//delete e;
				}
			} else {
				hero->move(0,0);
				oss << "No enemy at " << posToString(movePosn) << ". ";
			}
			return oss.str();
		}
	} else if (cmd[0] == 'u') {
		movePosn = getDirectionPos(cmd.substr(1));
		if (movePosn.x != 0 || movePosn.y != 0) {
			Position destination {heroPosn.x + movePosn.x
								, heroPosn.y + movePosn.y};
			shared_ptr<Potion> p = (dynamic_pointer_cast<Potion>(grid->
				occupant(destination.x, destination.y)));
			if (p != nullptr) {
				hero->usePotion(p.get());
				for (int i = 0; i < potions.size(); ++i) {
					if (p == potions[i]) {
						potions.erase(potions.begin() + i);
						break;
					}
				}
				grid->unoccupy(destination.x, destination.y);
				oss << "PC uses " << p->getName() << ". ";
				//delete p;
			} else {
				hero->move(0,0);
				oss << "No potion at " << posToString(movePosn) << ". ";
			}
			return oss.str();
		}
	} else {
		movePosn = getDirectionPos(cmd);
		if (movePosn.x != 0 || movePosn.y != 0) {
			Position destination {heroPosn.x + movePosn.x
								, heroPosn.y + movePosn.y};
			if (grid->isStair(destination.x, destination.y)) {
				movedToStair = true;
				return "Moved to next floor. ";
			}

			shared_ptr<Treasure> t = (dynamic_pointer_cast<Treasure>(grid->
				occupant(destination.x, destination.y)));
			if (t != nullptr) {
				grid->unoccupy(heroPosn.x, heroPosn.y);
				grid->unoccupy(destination.x, destination.y);
				grid->occupySpace(destination.x, destination.y, hero);
				hero->move(movePosn.x, movePosn.y);
				oss << "PC moved " << posToString(movePosn) << ". ";
				if (t->bePickedUpBy(hero)) {
					for (int i = 0; i < treasures.size(); ++i) {
						if (t == treasures[i]) {
							treasures.erase(treasures.begin() + i);
							break;
						}
					}
					oss << "PC picked up a " << t->getName() << ". ";
					if (hoard) {
						grid->occupySpace(heroPosn.x, heroPosn.y, hoard);
						hoard = nullptr;
					}
					//delete t;
				} else {
					hoard = dynamic_pointer_cast<DragonHoard>(t);
				}
			} else if (grid->occupySpace(destination.x, destination.y, hero)) {
				grid->unoccupy(heroPosn.x, heroPosn.y);
				hero->move(movePosn.x, movePosn.y);
				oss << "PC moved " << posToString(movePosn) << ". ";

				if (hoard) {
					grid->occupySpace(heroPosn.x, heroPosn.y, hoard);
					hoard = nullptr;
				}
			} else {
				hero->move(0,0);
				oss << "PC cannot move " << posToString(movePosn) << ". ";
			}
			return oss.str();
		} 
	}

	throw Controller::InvalidCommend{};
}

void Controller::availablePosns(const Position &center, vector<Position> &posns, 
								shared_ptr<Object> obj) {
	if (grid->canBeOccupied(center.x + 1, center.y + 1, obj)) {
		posns.emplace_back(1, 1);
	}
	if (grid->canBeOccupied(center.x, center.y + 1, obj)) {
		posns.emplace_back(0, 1);
	}
	if (grid->canBeOccupied(center.x + 1, center.y, obj)) {
		posns.emplace_back(1, 0);
	}
	if (grid->canBeOccupied(center.x - 1, center.y - 1, obj)) {
		posns.emplace_back(-1, -1);
	}
	if (grid->canBeOccupied(center.x - 1, center.y, obj)) {
		posns.emplace_back(-1, 0);
	}
	if (grid->canBeOccupied(center.x, center.y - 1, obj)) {
		posns.emplace_back(0, -1);
	}
	if (grid->canBeOccupied(center.x + 1, center.y - 1, obj)) {
		posns.emplace_back(1, -1);
	}
	if (grid->canBeOccupied(center.x - 1, center.y + 1, obj)) {
		posns.emplace_back(-1, 1);
	}
}

string Controller::moveAllEnemies() {
	ostringstream action;

	sort(enemies.begin(), enemies.end(), 
		[](shared_ptr<Enemy> e1, shared_ptr<Enemy> e2) { return *e1 < *e2; });
	Position heroPosn = hero->getPosition();
	for (auto e : enemies) {
		if (e->detectHero(heroPosn)) {
			int damage = e->attack(hero.get());
			action << e->getSymbol() << " deals " << damage << " damage to PC. ";
		} else if (moveEnemy) {
			vector<Position> posns;
			availablePosns(e->getPosition(), posns, e);
			if (posns.size() > 0) {
				Position movePosn = posns[rand() % posns.size()];
				Position curPos = e->getPosition();
				grid->unoccupy(curPos.x, curPos.y);
				e->move(movePosn.x, movePosn.y);
				curPos = e->getPosition();
				grid->occupySpace(curPos.x, curPos.y, e);
			}
		}
	}

	return action.str();
}

void Controller::initBoard() {
	grid = make_shared<Grid>();
	attach(grid->getDisplay());

	readMap(map);

	if (floorPopulated) {
		for (auto h : hoards) {
			for (auto d : dragons) {
				if (h->detectHero(d->getPosition())) {
					h->setDragon(d.get());
					d->setHoard(h.get());
				}
			}
		}
		hoards.clear();
		dragons.clear();
	} else {
		initChambers();
		spawnAll();
		/*for (auto c : chambers) {
			delete c;
		}*/
		chambers.clear();
	}

	setUp();

	notifyObservers("Player Character has spawned");

	out << *grid;
}

void Controller::startGame(char race, string mapFile) {
	floor = 1;
	hero = constructHeroFromCommand(race);
	map = mapFile;
	initBoard();
}

bool Controller::update(std::string cmd) {
	ostringstream oss;

	if (cmd == "f") {
		moveEnemy = !moveEnemy;
	} else {
		try {
			oss << evaluateCommend(cmd);
		} catch (InvalidCommend ic) {
			out << "Invalid Commend";
			return false;
		}
	}

	if (movedToStair) {
		hero->resetStats();
		clearBoard();
		++floor;
		if (floor == 6) {
			out << "Congratulations! " <<
				"You got to the stair on the fifth floor!" << endl;
			out << "Your final score is " << getScore() << '!' << endl;
			exitGame();
			return false;
		}
		initBoard();
		movedToStair = false;
	}

	

	oss << moveAllEnemies();
	notifyObservers(oss.str());
	out << *grid;

	if (hero->isDead()) {
		out << "Your final score is " << getScore() << endl;
		exitGame();
		return false;
	} else {
		return true;
	}
}

void Controller::clearBoard() {
	/*delete grid.get();
	grid = nullptr;*/

	/*for (auto p : potions) {
		delete p;
	}*/
	potions.clear();
	
	/*for (auto t : treasures) {
		delete t;
	}*/
	treasures.clear();
	
	/*for (auto e : enemies) {
		delete e;
	}*/
	enemies.clear();
}

void Controller::exitGame() {
	//delete hero;
	clearBoard();
}

int Controller::getScore() const {
	return hero->getScore();
}

void Controller::notifyObservers(string msg) const {
	for (auto & ob : observers) {
		if (msg != "") {
			ob->notify(msg);
		}
		ob->notify(hero, floor);
	}
}

Controller::~Controller() { 
	exitGame(); 
}
