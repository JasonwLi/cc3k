#include <string>
#include <iostream>
#include "Treasure.h"
#include "Enemy.h"
#include "Tile.h"

using namespace std;

//Constructor
Treasure::Treasure(string type, char symbol, int value, string valType): Item(type, valType, symbol), value(value), valType(valType) {

}

//Destructor
Treasure::~Treasure() {}

//get the value of the treasure
int Treasure::getValue() {
	return value;
}

//get the type of gold
string Treasure::getGoldType() {
	return valType;
}

Dragon* Treasure::getDragon() {
	return nullptr; //base class default 
}

void Treasure::deleteDragon() {
	return;
}

/* Dragonhoard */

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

/* Other Hoards*/
SmallHoard::SmallHoard(): Treasure("treasure", 'G', 1, "SmallHoard") {}

SmallHoard::~SmallHoard() {}

NormalHoard::NormalHoard(): Treasure("treasure", 'G', 2, "NormalHoard") {}

NormalHoard::~NormalHoard() {}

MerchantHoard::MerchantHoard(): Treasure("treasure", 'G', 4, "MerchantHoard") {}

MerchantHoard::~MerchantHoard() {}