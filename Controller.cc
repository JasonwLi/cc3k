#include <string>
#include <iostream>
#include <fstream>
#include "Controller.h"
#include "Player.h"
#include "Enemy.h"
#include "Treasure.h"
#include "Tile.h"

using namespace std;

//Constructor
Controller::Controller() {
	fileName = "";
	game = new Game(25,79); //25 rows and 79 columns
	display = new TextDisplay(25,79);
}

//Destructor
Controller::~Controller(){
	delete display;
	delete game;
}

void Controller::init() {
	game->init(this);
}

void Controller::startGame() {
	//set level back to 0
	//clear the floor
	createPlayer();//create new players
	if(fileName == ""){
	game->createFloor(); //create floor in the game		
	} else {
  game->loadFloor(fileName); //floor plan given
	}
	play();//play
}

void Controller::loadFloor(string floorFile) {
	fileName = floorFile;
	fstream file(fileName);
	string line = "", floorPlan = "";
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
			floorPlan += line + "\n";
		}
	} else {
		fileName = ""; //reset back to blank, since file cant be opened
		cout << "Failed to open file!" <<endl;
	}
	//cout << floorPlan; //FOR TESTING
}

void Controller::createPlayer() {
	//delete all existing player
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
	game->setPlayer(player); //set the player of the game based on the race chosen
}

void Controller::newFloor() {
	cout << "controller new floor"<<endl;
	game->createFloor();
}

void Controller::notify(int row, int col, char c) {
	cout << "controller notify"<<endl;
	td->notify(row, col, c);
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
	game->clearFloor();	//clear the floor
	game->createFloor();//create floor on the game
}

void checkEnemiesHP(Player* pc, Enemy** allEnemies) {
	for(int i=0;i<20;i++) {
		Enemy* enemy = allEnemies[i];
		if(enemy && enemy->getHP() == 0) {
			//enemy's HP is 0(enemy is dead)
			if(pc->getRace() == "Goblin") {
				//goblin can steal 5 gold from slain enemy
				pc->addGold(5);
			}
			enemy->dropGold(); //enemy drop gold when they died
			enemy->setPosition(nullptr);
			//delete and deallocate memory for slain enemy
			delete enemy;
			enemy = nullptr;
		}
	}
}

void Controller::play() {
	bool pauseEnemies = false;
	bool playerIsDead = false;
	string msg = "";

	while(true) {
		Player *pc = game->getPC(); //get the race 
		playerRace = pc->getRace();
		bool dgnAtk = false;
//	td->print(cout);
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
			string moveResult = pc->movePlayer(cmd); //move player with direction
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
					if(floorPlan == "") {
						newFloor(); //floor plan is not from a file
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
		Tile** neighbours = pc->getPosition()->getNeighbour();
		Enemy** allEnemies = game->getEnemies();

		checkEnemiesHP(pc, allEnemies); //check if enemies are dead or not
		
		//enemies attack player
		for(int i=0;i<8;i++) {
			Enemy* enemy = nullptr;
			Component* c = neighbours[i]->getComponent();
			if(c && c->getType() == "treasure") {
				//object is a treasure
				string goldType = static_cast<Treasure*>(c)->getGoldType() ;
				if(goldType == "DragonHoard") {
					//gold is dragon value = 6
					//can only be picked up when the dragon is slain
					enemy = static_cast<DragonHoard*>(c)->getDragon();
					if(enemy) {
						enemy->clearAttack();
					}
				}
			} else if(c && c->getType() == "enemy") {
				//object is an enemy
				enemy = static_cast<Enemy*>(c);
				string enemyRace = enemy->getRace();
				if(enemyRace == "Dragon") {
					enemy->clearAttack();
				}
			}

			//check if enemy exist
			if(enemy) {
				//check if enemy has attacked player or not
				if(!enemy->hasAttackedPlayer()) {
					if(enemyRace == "Dragon" && dgnAtk) {
						if(dgnAtk) continue;
						else dgnAtk = true;
					}
					//enemy attack/hit player
					msg += enemy->hit(pc);
					enemy->attackedPlayer();
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
					if(!allEnemies[i]->hasAttackedPlayer()) {
						//enemy is still alive and have not attacked player
						int counter = 0;
						string moveResult = "nomovement";
						int moveNum = rand() % 4;
						while(counter < 8 && moveResult == "nomovement") {
							moveResult = allEnemies[i]->moveEnemy(moveNum);
							counter++;
						}
					}
					allEnemies[i]->clearAttack();
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
