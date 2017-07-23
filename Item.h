#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <iostream>
//#include "Component.h"

class Item: public Component {
	public:
		Item(char symbol, std::string name, std::string type);
		~Item();
};

#endif
