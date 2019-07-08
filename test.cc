#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "controller.h"
using namespace std;

char chooseRace() {
	string cmd = "";
	cout << "Choose your race, available opitons are \"s, d, v, g, t\"" 
		 << endl;
	while (cin >> cmd) {
		if (cmd == "s" || cmd == "d" || cmd == "v" 
			|| cmd == "g" || cmd =="t") {
			return cmd[0];
		} else {
			cout << "Invalid race, available opitons are \"s, d, v, g, t\""
				 << endl;
		}
	}

	return ' ';
}

bool strInArr(string str, string (&arr)[8]) {
	for (int i = 0; i < 8; ++i) {
		if (str == arr[i]) {
			return true;
		}
	}

	return false;
}

int main(int argc, char *argv[]) {
	string mapFile = "floor.txt";
	
	if (argc - 1 > 0) {
		mapFile = argv[1];
	}
	if (argc - 1 > 1) {
		istringstream iss{argv[2]};
		int seed;
		if (iss >> seed) {
			srand(seed);
		}
	} else {
		srand(time(NULL));
	}

	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	Controller c;
	bool gameOver = false;

	char race = chooseRace();
	if (race == ' ') {
		cout << "No more input, exiting program." << endl;;
		return 0;
	} else {
		c.startGame(race, mapFile);
	}

	string directions[8] = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};

	try {
		while (!gameOver) {
			cout << "Command: " << endl;
			cin >> cmd;
			if (cmd == "q") {
				c.exitGame();
				cout << "Quit game" << endl;
				return 0;
			} else if (cmd == "r") {
				c.exitGame();
				cout << "Restart game" << endl;

				race = chooseRace();
				if (race == ' ') {
					cout << "No more input, exiting program." << endl;
					return 0;
				} else {
					c.startGame(race, mapFile);
				}
			} else if (cmd == "f" || strInArr(cmd, directions) || 
				((cmd[0] == 'a' || cmd[0] == 'u') 
					&& strInArr(cmd.substr(1), directions))) {
				gameOver = !c.update(cmd);
			} else {
				cout << "Invalid commend" << endl;
			}
		}
	} catch (ios::failure & expt) {
		c.exitGame();
 		cout << "No more input, exiting program." << endl;
 	}
}
