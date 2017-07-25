#ifndef _DRAGONHOARD_H
#define _DARGONHOARD_H

#include <string>
#include <iostream>
#include "Treasure.h"
#include "Item.h"
#include "Enemy.h"

class DragonHoard: public Treasure {
	Dragon* dragon;
	bool dragonIsSlain;
	public:
		DragonHoard();
		DragonHoard(Dragon* dragon);
		Dragon* getDragon();
		void slayDragon();
		void setDragon(Dragon* dragon);
		~DragonHoard();
};

#endif
