#include <string>
#include <iostream>
#include "DragonHoard.h"

using namespace std;

DragonHoard::DragonHoard(): Treasure("treasure", 'G', 6, "DragonHoard") {
	dragon = new Dragon(this);
}

DragonHoard::DragonHoard(Dragon* dragon): Treasure("treasure", 'G', 6, "DragonHoard"), dragon(dragon) {

}

Dragon* DragonHoard::getDragon() {
	return dragon;
}

void DragonHoard::deleteDragon() {
	dragon->getPosition()->setComponent(nullptr);
	delete dragon;
	dragon = nullptr;
}

void DragonHoard::setDragon(Dragon* dragon) {
	this.dragon = dragon;
}

//destructor
DragonHoard::~DragonHoard() {
	if(dragon->getPosition() && dragon) {
		dragon->getPosition()->setComponent(nullptr);
	}
	delete dragon;
}
