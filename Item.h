#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <iostream>
#include "Component.h"

class Item: public Component {
	public:
		Item(std::string type, std::string name, char symbol);
		~Item();
};

#endif
