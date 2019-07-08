#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "position.h"
#include "subject.h"

class TextDisplay;
class Grid;
class Chamber;
class Object;
class Potion;
class Treasure;
class Enemy;
class Hero;
class Dragon;
class DragonHoard;

class Controller : public Subject {
	int numRow = 25;
	int numCol = 79;
	int numChamber = 5;
	int numPotion = 10;
	int numTreasure = 10;
	int numEnemy = 20;

	bool floorPopulated = false;
	bool moveEnemy = true;

	// tempoarily holds the dragon hoard whichthe PC is standing on.
	std::shared_ptr<DragonHoard> hoard;

	// tempoarily holds the dragons and hoards that were created from
	//   reading a populated floor map
	std::vector<std::shared_ptr<DragonHoard>> hoards;
	std::vector<std::shared_ptr<Dragon>> dragons;

	std::ostream &out;
	std::istream &in;
	std::shared_ptr<Grid> grid;
	std::shared_ptr<Hero> hero;
	Position stairPosn;
	std::vector<std::shared_ptr<Chamber>> chambers;
	std::vector<std::shared_ptr<Potion>> potions;
	std::vector<std::shared_ptr<Treasure>> treasures;
	std::vector<std::shared_ptr<Enemy>> enemies;
	int floor;
	bool movedToStair = false;
	std::string map;

	void initChambers();
	Position randomPosnFromChamber(int choosenChamber = -1);
	bool randomAdjacentPosnsFromChamber(std::vector<Position> &);
	void readMap(std::string fileName);
	void spawnAll();
	std::string moveAllEnemies();
	void availablePosns(const Position &center, std::vector<Position> &posns
						, std::shared_ptr<Object> obj);
	// places all spawned objects on to the grid
	void setUp();
	std::string evaluateCommend(std::string cmd);
	void initBoard();
	void clearBoard();
public:
	class InvalidCommend {
		InvalidCommend() = default;
	public:
		~InvalidCommend() = default;
		friend class Controller;
	};

	Controller(std::ostream &out = std::cout, std::istream &in = std::cin);

	void startGame(char race, std::string mapFile);
	bool update(std::string cmd);
	void exitGame();
	int getScore() const;
	void notifyObservers(std::string msg = "") const override;
	void nextFloor();

	// for testing
	void printGrid(std::ostream & out) const;
	void printChamber(std::ostream & out) const;
	
	~Controller();	
};

#endif
