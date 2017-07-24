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

/* Other Hoards*/
SmallHoard::SmallHoard(): Treasure("treasure", 'G', 1, "SmallHoard") {}

SmallHoard::~SmallHoard() {}

NormalHoard::NormalHoard(): Treasure("treasure", 'G', 2, "NormalHoard") {}

NormalHoard::~NormalHoard() {}

MerchantHoard::MerchantHoard(): Treasure("treasure", 'G', 4, "MerchantHoard") {}

MerchantHoard::~MerchantHoard() {}