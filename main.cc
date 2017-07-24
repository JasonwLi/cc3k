#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Controller.h"

using namespace std;

int main(int argc, char* argv[]) {
	Controller controller;
	if(argc > 0 && argc < 4) { //between 1-3
		int seed = time(NULL);
		if(argc == 3) {
			seed = stoi(argv[2]);
		}
		srand(seed);
		controller.initController();
		if(argc > 1) {
			//load floor from a file
			controller.loadFloor(argv[1]);
		} 
		//start the game
		controller.startGame();
	} else {
		cout << "Usage: ./cc3k [filename] [seed]" << endl;
	}
}