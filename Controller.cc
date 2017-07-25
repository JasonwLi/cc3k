#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Controller.h"
#include "Player.h"
#include "Enemy.h"
#include "Treasure.h"
#include "Tile.h"

using namespace std;

//Constructor
Controller::Controller() {
	fileName = "";
	floorPlanLoaded = "";
	game = new Game(25,79); //25 rows and 79 columns
	display = new TextDisplay(25,79);
}

//Destructor
Controller::~Controller(){
	delete display;
	delete game;
}

void Controller::initController() {
	game->init("sample_floor.txt", this);
}

void Controller::startGame() {
	game->setLevel(0); //set level to 0
	createPlayer();//create new players
	if(floorPlanLoaded == ""){
		game->buildFloor(); //create floor in the game		
	} else {
  	game->loadFloor(floorPlanLoaded); //floor plan given
	}
	play();//play
}

void Controller::loadFloor(string floorFile) {
	fileName = floorFile;
	fstream file(fileName);
	string line = "";
	int row  = game->getRow(); //get the # of rows of the floor
	int level = game->getLevel(); //get the current level

	if(file.is_open()) {
		for(int i=0;i<level*row;i++) {
			//loop through floorPlan until it gets to the right level
			getline(file, line);
		}

		for(int j=0;j<row;j++) {
			//get the floorplan of the level
			getline(file, line);
			floorPlanLoaded += line + "\n";
		}
	} else {
		fileName = ""; //reset back to blank, since file cant be opened
		floorPlanLoaded = "";
		cout << "Failed to open file! Floor will be empty." <<endl;
	}
	//cout << floorPlanLoaded; //FOR TESTING
}

void Controller::createPlayer() {
	//ask for a character, or else, it will be default Shade
	string race = "shade"; //default race
	Player* player;
	while(true) {
		cout << "Choose a race as your character:"<<endl;
		cout << "s: shade, d: drow, v: vampire, t: troll, g: goblin" <<endl;
		char c;
		cin >> c;
		if(c == 's') {
			//shade
			race = "shade";
			player = new Shade();
			break;
		} else if(c == 'd') {
			//drow
			race = "drow";
			player = new Drow();
			break;
		} else if(c == 'v') {
			//vampire
			race = "vampire";
			player = new Vampire();
			break;
		} else if(c == 'g') {
			//goblin
			race = "goblin";
			player = new Goblin();
			break;
		} else if(c == 't') {
			//troll
			race = "troll";
			player = new Troll();
			break;
		} else {
			cout << "choose a player!" << endl;
		}
	}
	cout << "Race chosen: "<<race<<endl;
	cout << "Start the game" <<endl;
	game->setPC(player); //set the player of the game based on the race chosen
}

void Controller::notify(int row, int col, char c) {
	display->notify(row, col, c);
}

void printSpaces(int total) {
	for(int i=0;i<total;i++) {
		cout << " ";
	}
}

void Controller::printStatus(string msg) {
	//default values to be printed
	string Race = "";
	string Gold = "0";
	string HP = "0";
	string Atk = "0";
	string Def = "0";
	string Action = "";

	string level = to_string(game->getLevel()); //get current floor level
	Player* pc = game->getPC(); //get the current player of the game

	if(pc) { //if player exists
		Race = pc->getRace();
		Gold = to_string(pc->getGold());
		HP = to_string(pc->getHP());
		Atk = to_string(pc->getAtk());
		Def = to_string(pc->getDef());
	}

	//display/print status of the player in the game
	cout << "Race: " << Race << " Gold: " << Gold;
	printSpaces(50);
	cout << "Floor "<< level << endl;
	cout << "HP: " << HP << endl;
	cout << "Atk: " << Atk << endl;
	cout << "Def: " << Def << endl;
	cout << "Action: " << msg << endl;

	return;
}

void Controller::restart() {
	createPlayer(); //create players
	game->setLevel(0);//set level back to 0
	game->buildFloor();//create floor on the game
}

void checkEnemiesHP(Player* &pc, vector<Enemy*> &allEnemies) {
	for(int i=0;i<20;i++) {
		Enemy* enemy = allEnemies[i];
		string enemyRace = enemy->getRace();
		if(enemy && enemy->getHP() == 0) {
			//enemy's HP is 0(enemy is dead)
			if(pc->getRace() == "Goblin") {
				//goblin can steal 5 gold from slain enemy
				pc->addGold(5);
			}

			if(enemyRace != "Human" || enemyRace != "Merchant" || enemyRace != "Dragon") {
				//not human, merchant or dragon
				int goldValue = rand() % 2 + 1; //1 or 2
				pc->addGold(goldValue); //add gold immediately
			} else {
				enemy->dropHoard(); //enemy drop gold when they died
			}
			//delete and deallocate memory for slain enemy
			delete enemy;
			enemy = nullptr;
		}
	}
}

string getDirection(int moveNum) {
	string dir="ea";
	switch(moveNum) {
		case 0:
			dir = "no";
			break;
		case 1:
			dir = "we";
			break;
		case 2:
			dir = "so";
			break;
		case 3:
			dir = "ea";
			break;
		case 4:
			dir = "nw";
			break;
		case 5:
			dir = "ne";
			break;
		case 6:
			dir = "sw";
			break;
		case 7:
			dir = "se";
			break;
	}
	return dir;
}

void Controller::play() {
	bool pauseEnemies = false;
	bool playerIsDead = false;
	string msg = "";

	while(true) {
		Player *pc = game->getPC(); //get the race 
		string playerRace = pc->getRace();
		bool dgnAtk = false;
		display->print(cout);
		printStatus(msg);
		msg = "";

		//check if player is dead
		if(playerIsDead) {
			cout << "You are dead! Start a new game? [y/n]" <<endl;
			string startNewGame;
			cin >> startNewGame;
			if(startNewGame == "y") {
				playerIsDead = false;
				msg += "The game is restarted.";
				restart();
			} else {
				return;
			}
		}	

		//read the command one by one
		string cmd;
		cin >> cmd;
		if(cin.eof()) return;
		if(cmd == "q") {
			cout << "Are you sure you want to quit the game? [y/n]"<<endl;
			string quitGame;
			cin >> quitGame;
			if(quitGame == "y") return;
			else if(quitGame == "n") continue;

		} else if(cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" ||
			cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
			//direction
			string moveResult = pc->playerMove(cmd); //move player with direction
			if(moveResult != "moved") {
				msg += moveResult + cmd + ".";
				continue;
			} else if(moveResult == "nextLevel") {
				//up to the next level
				if(game->getLevel() == 5) {
					//highest level reached!

					//get final score
					int finalScore = pc->getGold();
					if(playerRace == "Shade") finalScore = finalScore * 1.5;

					//print message and score
					cout << "Congratulations, You've reached the highest level!"<<endl;
					cout << "Final score: " << finalScore << endl;
					
					//ask if user wants to restart game
					cout << "Play a new game? [y/n]"<<endl;
					string restartGame;
					cin >> restartGame;
					if(restartGame == "y") {
						playerIsDead = false;
						msg += "The game is restarted.";
						restart();
					} else if(restartGame == "n") {
						return;
					}
				} else {
					//go to a higher level
					if(floorPlanLoaded == "") {
						game->buildFloor(); //floor plan is not from a file
					} else {
						//flor plan is from a file to be loaded
						loadFloor(fileName);
					}
				}
			} else {
				msg += moveResult + cmd + ".";
			}

		} else if(cmd == "f") {
			//stops enemies from moving until this key is pressed again
			pauseEnemies = !pauseEnemies;
			continue;

		} else if(cmd == "r") {
			//restart
			playerIsDead = false;
			msg += "The game is restarted.";
			restart();
			continue;

		} else if(cmd == "u") {
			//uses the potion
			string direction;
			cin >> direction; //get the direction
			msg += game->usePotion(direction); //use potion in s certain direction
		
		} else if(cmd == "a") {
			//attacks enemy, enemy must be one block away from PC
			string direction;
			cin >> direction; //get the direction
			string attackResult = game->attack(direction); //try to attack
			if(attackResult != "failedAttack") {
				//successful attack
				msg += attackResult;
			} else if(attackResult == "noEnemy") {
				//failed attack
				msg += "No enemy found on " + direction + ".";
				continue;
			}
		} else {
			msg += "Wrong input!";
			continue;
		}
		//check if player's health points is 0 or not
		if(pc->getHP() == 0) {
			playerIsDead = true;
			continue;
		}

		//get the neighbours and all enemies
		Tile** neighbourTiles = pc->getLocation()->getNeighbours();
		vector<Enemy*> allEnemies = game->getEnemies();

		checkEnemiesHP(pc, allEnemies); //check if enemies are dead or not
		
		//enemies attack player
		for(int i=0;i<8;i++) {
			Enemy* enemy = nullptr;
			Component* c = neighbourTiles[i]->getComponent();
			if(c && c->getType() == "treasure") {
				//object is a treasure
				string goldType = static_cast<Treasure*>(c)->getGoldType() ;
				if(goldType == "DragonHoard") {
					//player is wthin dragonhoard radius
					enemy = static_cast<DragonHoard*>(c)->getDragon();
					if(enemy) {
						enemy->setInactive(); //dragon should not move
					}
				}
			} else if(c && c->getType() == "enemy") {
				//object is an enemy
				enemy = static_cast<Enemy*>(c);
				string enemyRace = enemy->getRace();
				if(enemyRace == "Dragon") {
					enemy->setInactive(); //dragon should not move
				}
			}

			//check if enemy exist
			if(enemy) {
				//check if enemy has attacked player or not
				string enemyRace = enemy->getRace();
				if(!enemy->ifActive()) {
					if(enemyRace == "Dragon") {
						if(dgnAtk) continue;
						else dgnAtk = true;
					}
					//enemy attack/hit player
					msg += enemy->hit(pc);
					enemy->setActive(); //enemy is set to active
					//chekc if player is dead
					if(pc->getHP() == 0) {
						playerIsDead = true;
						continue;
					}
				}
				//enemy exist
				if(enemyRace == "Merchant" && !enemy->isHostile()) {
					//merchant is friendly
					msg += "Merchant is not hostile.";
					continue;
				}
			}
		}

		//move enemies to a different tile randomly if they
		if(!pauseEnemies) {
			for(int i=0;i<20;i++) {
				if(allEnemies[i]) {
					if(!allEnemies[i]->ifActive()) {
						//enemy is still alive and have not attacked player
						int counter = 0;
						string moveResult = "Blocked";
						while(counter < 8 && moveResult == "Blocked") {
							int moveNum = rand() % 8;
							string moveDir = getDirection(moveNum);
							moveResult = allEnemies[i]->move(moveDir);
							counter++;
						}
					}
					allEnemies[i]->setInactive();
				}
			}
		}

		//if player is troll and still alive, regain 5 HP every turn
		if(playerRace == "Troll" && !playerIsDead && pc->getHP() != pc->getMaxHP()) {
			pc->heal(5); //regain 5 HP
			msg += "Regained 5 HP.";
		}
	}
}
