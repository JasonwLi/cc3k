#include "Potion.h"
#include <string>

using namespace std;

//Constructor
Potion::Potion(string potEffect) : Item("potion", potEffect, 'P'), potEffect(potEffect) {}

//Destructor
Potion::~Potion() {}

//get effect of potion
string Potion::getEffect() {
	return potEffect;
}
