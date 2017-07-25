#include <string>
#include <iostream>
#include "DragonHoard.h"
#include "Tile.h"

using namespace std;

DragonHoard::DragonHoard(): Treasure("treasure", 'G', 6, "DragonHoard") {
	dragon = new Dragon(this); //set dragon with its dragonhoard
	dragonIsSlain = false;
}

DragonHoard::DragonHoard(Dragon* dragon): Treasure("treasure", 'G', 6, "DragonHoard"), dragon(dragon) {

}

Dragon* DragonHoard::getDragon() {
	return dragon;
}

void DragonHoard::setDragon(Dragon* dragon) {
	this->dragon = dragon;
}

void DragonHoard::slayDragon() {
	dragonIsSlain = true;
	dragon->getLocation()->setComponent(nullptr);
	delete dragon;
	dragon = nullptr;
}

//destructor
DragonHoard::~DragonHoard() {
	if(!dragonIsSlain) {
		dragon->getLocation()->setComponent(nullptr);
	}
	delete dragon;
	dragon = nullptr;
}