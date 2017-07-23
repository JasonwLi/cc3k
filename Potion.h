#ifndef _POTION_H
#define _POTION_H

#include <string>
#include <iostream>
#include "Item.h"

class Potion: public Item {
	string potEffect;
	public:
		Potion(string potEffect);
		~Potion();
		std::string getEffect();
};

#endif
