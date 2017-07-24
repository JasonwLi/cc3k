#ifndef PROJECT_EFFECTDECO_H
#define PROJECT_EFFECTDECO_H

#include "Effect.h"

class boostAtk: public Effect{
public:
    boostAtk(int change, Player* player);
    ~boostAtk();
    int getAtk();
};

class boostDef: public Effect{
public:
    boostDef(int change, Player* player);
    ~boostDef();
    int getDtk();
};

#endif //PROJECT_EFFECTDECO_H
