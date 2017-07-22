#include <string>
#include <iostream>
#include <fstream>
#include "Controller.h"

using namespace std;

//Constructor
Controller::Controller() {
	cout << "Controller Constructor"<<endl;
	fileName = "";
//	game = new Game(25,79); //25 rows and 79 columns
//	display = new TextDisplay(25,79);
}

//Destructor
Controller::~Controller(){
//	delete display;
//	delete game;
}

void Controller::init() {
	cout << "controller init" <<endl;
//	game->init(this);
}

void Controller::startGame() {
	cout << "controller start new game"<<endl;
	//set level back to 0
	//clear the floor
	createPlayer();//create new players
	if(fileName == ""){
//	game->createFloor(); //create floor in the game		
	} else {
//  game->loadFloor(fileName); //floor plan given
	}
	play();//play
}

void Controller::loadFloor(string floorFile) {
	cout << "controller load file"<<endl;
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
	cout << "controller create player"<<endl;
	//delete all existing player
	//ask for a character, or else, it will be default Shade
	string race = "shade"; //default race
//	Player* player;
	while(true) {
		cout << "Choose a race as your character:"<<endl;
		cout << "s: shade, d: drow, v: vampire, t: troll, g: goblin" <<endl;
		char c;
		cin >> c;
		if(c == 's') {
			//shade
			race = "shade";
//			player = new Shade();
			break;
		} else if(c == 'd') {
			//drow
			race = "drow";
//			player = new Drow();
			break;
		} else if(c == 'v') {
			//vampire
			race = "vampire";
//			player = new Vampire();
			break;
		} else if(c == 'g') {
			//goblin
			race = "goblin";
//			player = new Goblin();
			break;
		} else if(c == 't') {
			//troll
			race = "troll";
//			player = new Troll();
			break;
		} else {
			cout << "choose a player!" << endl;
		}
	}
	cout << "Race chosen: "<<race<<endl;
	cout << "Start the game" <<endl;
//	game->setPlayer(player); //set the player of the game based on the race chosen
}

void Controller::newFloor() {
	cout << "controller new floor"<<endl;
//	game->createFloor();
}

void Controller::notify(int row, int col, char c) {
	cout << "controller notify"<<endl;
//	td->notify(row, col, c);
}

void Controller::printStatus(string msg) {
	cout << "controller print status"<<endl;

}

void Controller::restart() {
	cout << "controller restart"<<endl;
//	game->setLevel(0);//set level back to 0
//  game->clearFloor();	//clear the floor
	createPlayer(); //create players
//	game->createFloor();//create floor on the game
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
	cout << "controller play"<<endl;
	bool pauseEnemies = false;
	bool playerIsDead = false;
	string msg = "";
	while(true) {
		Player *pc = game->getPC(); //get the race 
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
				//move but nothing special
				msg += moveResult + cmd + ".";
				continue;
			} else if(isdigit(moveResult[0])) {
				//move and pick up gold
				msg += "You moved to "+cmd+" and you found "+moveResult+" golds.";
			} else if(moveResult == "nextLevel") {
				//up to the next level
				if(game->getLevel() == 5) {
					//highest level reached!

					//get final score
					int finalScore = pc->getGold();
					if(pc->getRace() == "Shade") finalScore = finalScore * 1.5;

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
				} else  {
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
			} else {
				//failed attack
				msg += "No enemy found on " + direction + ".";
				continue;
			}
		} else {
			msg += "Invalid input!";
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
			Component* c = neighbours[i]->getComponent();
			Enemy* enemy = nullptr;
			if(c && c->getType() == "enemy") {
				enemy = static_cast<Enemy*>(c);
				if(c->getRace() == "Dragon") {
					// actclear() ????
				}
			} else if(c && c->getType() == "treasure") {
				//object is a treasure
				if(static_cast<Treasure*>(c)->getGoldValue() == "Dragon") {
					//gold is dragon value = 6
					//can only be picked up when the dragon is slain
					enemy = static_cast<DragonHoard*>(c)->getDragon();
					if(enemy) {
						enemy->clearAttack();
					}
				}
			}

			//component is enemy
			if(enemy) {
				string enemyRace = e->getRace();
				//enemy exist
				if(enemyRace == "Merchant" && !e->isHostile()) {
					//merchant is friendly
					msg += "Merchant is not hostile.";
					continue;
				}
				//check if enemy has attacked player or not
				if(!enemy->hasAttackedPlayer()) {
					if(enemy->getRace() == "Dragon" && dgnAtk) {
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
			}
		}

		//move enemies to a different tile randomly
		if(!pauseEnemies) {
			for(int i=0;i<20;i++) {
				if(allEnemies[i]) {
					if(!allEnemies[i]->hasAttackedPlayer()) {
						//enemy is still alive and have not attacked player
						int counter = 0;
						string moveResult = "nomovement"
						while(counter < 8 && moveResult == "nomovement") {
							int moveNum = rand() % 4;
							moveResult = allEnemies[i]->moveEnemy(moveNum);
							counter++;
						}
					}
					allEnemies[i]->clearAttack();
				}
			}
		}

		//if player is troll and still alive, regain 5 HP every turn
		if(pc->getRace() == "Troll" && !playerIsDead && pc->getHP() != pc->getMaxHP()) {
			pc->heal(5); //regain 5 HP
			msg += "Regained 5 HP."
		}
	}
}
