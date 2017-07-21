#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <string>
#include <iostream>
//#include "Game.h"
// class Game;

class Controller {
//	Game* game;
	public:
		Controller();
		~Controller();
		void init();
		void play();
		void loadFile(std::string fileName);
		void createPlayer();
		void startNewGame();
		void newFloor();
		void notify(int row, int col, char c);
		void printStatus(std::string msg);
		void restart();
		void quit();
};

#endif