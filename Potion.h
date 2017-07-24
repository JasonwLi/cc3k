#ifndef _POTION_H
#define _POTION_H

#include <string>
#include <iostream>
#include "Item.h"

class Potion: public Item {
	std::string potEffect;
	public:
		Potion(std::string potEffect);
		std::string getEffect();
		~Potion();
};

#endif
