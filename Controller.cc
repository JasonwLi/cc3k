#include <string>
#include <iostream>
#include <fstream>
#include "Controller.h"

using namespace std;

//Constructor
Controller::Controller() {
	cout << "Controller Constructor"<<endl;
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

void Controller::startNewGame() {
	cout << "controller start new game"<<endl;
	//set level back to 0
	//clear the floor
	createPlayer();//create new players
//	game->createFloor(); //create floor in the game
	play();//play
}

void Controller::loadFile(string fileName) {
	cout << "controller load file"<<endl;
	fstream file(fileName);
	string line, floor;
	if(file.is_open()) {
		while(getline(file, line)) {
			floor += line + "\n";
		}
//		game->loadFloor(floor);
	} else {
		cout << "Failed to open file!" <<endl;
	}
	cout << floor;
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
	//set level back to 0
	//clear the floor
	//create players
	//create floor on the fame
}

void Controller::play() {
	cout << "controller play"<<endl;
	//get the existing players
	//read the command one by one
	//check if enemies are dead or not
	//enemies attack player
	//move enemies to a different tile randomly
}

void Controller::quit() {

}