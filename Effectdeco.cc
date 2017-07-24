#include "Effectdeco.h"


boostAtk::boostAtk(int change, Player *player) :Effect(change, player){}
boostAtk::~boostAtk() {}
int boostAtk::getAtk() {
    if(change +  player->getAtk() <= 0) {
        return 0;
    }else{
        return change + player->getAtk();
    }
}

boostDef::boostDef(int change, Player *player) :Effect(change, player){}
boostDef::~boostDef() {}
int boostDef::getDef(){
    if(change +  player->getDef() <= 0) {
        return 0;
    }else{
        return change + player->getDef();
    }
}


