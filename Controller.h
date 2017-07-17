#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <string>
#include <iostream>
#include "Game.h"
class Game;

class Controller {
	Game* game;
	public:
		Controller();
		~Controller();
		void init();
		void play();
		void loadFile(string fileName);
		void createPlayer();
		void newFloor();
		void notify(int row, int col, char c);
		void printStatus(string msg);
		void restart();
		void quit();
}

#endif