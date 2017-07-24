#ifndef _DRAGONHOARDS_
#define _DARGONHOARDS_

#include <string>
#include <iostream>
#include "Treasure.h"
#include "Enemy.h"

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
