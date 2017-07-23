#ifndef _TREASURE_H
#define _TREASURE_H

#include <string>
#include <iostream>
#include "Item.h"
//class Enemy or Dragon

class Treasure: public Item {
	const int value;
	const std::string valType; //dragon, small, normal. merchant
	public:
		Treasure(std::string type, char symbol, int value, std::string valType);
		virtual ~Treasure() = 0;
		int getValue();
		std::string getGoldType();
		virtual Dragon* getDragon();
		virtual void deleteDragon();
};

class SmallHoard: public Treasure {
	public:
		SmallHoard();
		~SmallHoard();
};

class NormalHoard: public Treasure {
	public:
		NormalHoard();
		~NormalHoard();
};

class MerchantHoard: public Treasure {
	public:
		MerchantHoard();
		~MerchantHoard();
};

class DragonHoard: public Treasure {
	Dragon* dragon;
	public:
		DragonHoard();
		DragonHoard(Dragon* dragon);
		Dragon* getDragon();
		void deleteDragon();
		void setDragon(Dragon* dragon);
		~DragonHoard();
};

#endif
