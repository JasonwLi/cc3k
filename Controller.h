#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <string>
#include <iostream>
#include "Game.h"
#include "TextDisplay.h"
#include "Component.h"

class Controller {
	Game* game;
	std::string fileName;
	TextDisplay* display;
	public:
		Controller();
		~Controller();
		void init();
		void play();
		void loadFloor(std::string fileName);
		void createPlayer();
		void startGame();
		void newFloor();
		void notify(int row, int col, char c);
		void printStatus(std::string msg);
		void restart();
};

#endif
