#include "Enemy.h"
#include "Treasure.h"
#include "Tile.h"

using namespace std;

Enemy::Enemy(std::string race, int Atk, int Def, int HP, char symbol, string name, string type) :
        Character(race, Atk, Def, HP, symbol, name, type), active{false} {}

Enemy::~Enemy() {}

bool Enemy::ifActive(){
    return active;
}

void Enemy::setActive(){
    active = true;
}

void Enemy::setInactive(){
    active = false;
}

void Enemy::dropHoard(){
    return;
}

Human::Human():Enemy("Human", 20, 20, 140, 'H', "Human", "enemy"){}
Human::~Human(){}
void Human::dropHoard(){
    Treasure *first = new NormalHoard();
    Treasure *second = new NormalHoard();
    Tile* curr = this->getLocation();
    first->setLocation(curr);
    curr->setComponent(first);
    int i = 0;
    for(int d=0; d<8; d++){ //check all surrounding neighbours for empty place to put second hoard
        Tile* secondLoc = curr->getNeighbour(i);
        if(!secondLoc->getComponent() && secondLoc && secondLoc->getCh() == '.'){
            second->setLocation(secondLoc);
            secondLoc->setComponent(second);
            return;
        }
    }
    //if there is no where available to place the second hoard, just delete it
    delete second;
    return;
}

Dwarf::Dwarf():Enemy("Dwarf", 20, 30, 100, 'D',"Dwarf", "enemy"){}
Dwarf::~Dwarf(){}

Elf::Elf():Enemy("Elf", 30, 10, 140, 'E',"Elf", "enemy"){}
Elf::~Elf(){}

Orc::Orc():Enemy("Orc", 30, 25, 180, 'O',"Orc", "enemy"){}
Orc::~Orc(){}

bool Merchant::hostile = false;
Merchant::Merchant():Enemy("Merchant", 70, 5, 30, 'M',"Merchant", "enemy"){}
Merchant::~Merchant(){}

void Merchant::isHostile() {
    return hostile;
}

void Merchant::setHostile(bool hostile) {
    this->hostile = hostile;
}

void Merchant::dropHoard() {
    MerchantHoard* mHoard = new MerchantHoard();
    Tile *curr = this->getLocation();
    mHoard->setLocation(curr);
    curr->setComponent(mHoard); //now that the location is a mHoard instead of Merchant
}

Halfling::Halfling():Enemy("Halfling", 15, 20, 100, 'H',"Halfling", "enemy"){}
Halfling::~Halfling(){}

Dragon::Dragon() : Enemy("Dragon", 20, 20, 150, 'D', "enemy", "Dragon", "enemy"), dHoard(nullptr) {}
Dragon::Dragon(DragonHoard* dHoard) : Enemy("Dragon", 20, 20, 150, 'D', "enemy", "Dragon", "enemy"), dHoard(dHoard) {}
Dragon::~Dragon() {}
DragonHoard* Dragon::getHoard() {return dHoard;}
void Dragon::setHoard(DragonHoard *dHoard) {dHoard = dHoard;}

void Dragon::dropHoard() {
    return; //the Dragon Hoard is already around the Dragon
}
