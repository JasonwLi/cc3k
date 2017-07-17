#include <string>
#include <iostream>
#include <fstream>
#include "Controller.h"

using namespace std;

//Constructor
Controller::Controller() {
	game = new Game(25,79); //25 rows and 79 columns
}

//Destructor
Controller::~Controller(){
	delete game;
}

void Controller::init() {

}

void Controller::loadFile(string fileName) {
	ofstream file(fileName);
	string line, floor;
	if(file.is_open()) {
		while(getline(file, line)) {
			floor += line + "\n";
		}
		game->loadFloor(floor);
	} else {
		cout << "Failed to open file!" <<endl;
	}
}

void Controller::createPlayer() {

}

void Controller::newFloor() {

}

void Controller::notify(int row, int col, char c) {

}

void Controller::printStatus(string msg) {

}

void Controller::restart() {

}

void Controller::play() {

}

void Controller::quit() {

}