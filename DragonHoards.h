#ifndef _DRAGONHOARDS_
#define _DARGONHOARDS_

#include <string>
#include <iostream>
#include "Treasure.h"
#include "Item.h"

class Dragon;

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
