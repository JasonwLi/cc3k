#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <string>
#include <iostream>
#include "Game.h"
#include "Component.h"
#include "TextDisplay.h"

class Controller {
	Game* game;
	std::string fileName;
	std::string floorPlanLoaded;
	TextDisplay* display;
	public:
		Controller();
		~Controller();
		void initController();
		void play();
		void loadFloor(std::string fileName);
		void createPlayer();
		void startGame();
		void notify(int row, int col, char c);
		void printStatus(std::string msg);
		void restart();
};

#endif
