#include "Effect.h"
using namespace std;

//constructor takes in the player pointer inside decorator, other fields are set to default
Effect::Effect(int c, Player *player) :Player(0, 0, 0, 0, 0, "", ' ', ""), player{player}, change{c}{}
Effect::~Effect() {}

//all access to fields are set to player pointed by Player*
std::string Effect::getRace() { return player->race;}
int Effect::getAtk() { return player->Atk;}
int Effect::getDef() { return player->Def;}
int Effect::getHP() { return player->HP;}

char Effect::getSymbol(){ return player->symbol;}
std::string Effect::getName() { return player->name;}
std::string Effect::getType() { return player->type;}

int Effect::getMaxHP() { return player->maxHP;}
unsigned int Effect::getGold() { return player->gold;}

Player* Effect::getPlayer() {
    //delete this pointer, return the player* inside the decorator
    //so potion effects are cleaned up
    Player* temp = player->getPlayer();
    delete this;
    return temp;
}


void Effect::addGold(int g) {
    player->addGold;
    return;
}

void Effect::setGold(int g) {
    player->setGold;
    return;
}

void Effect::setAtk(int a) {
    Player->setAtk;
    return;
}

void Effect::setDef(int d) {
    Player->setDef;
    return;
}

void Effect::setHP(int h) {
    Player->setHP;
    return;
}

std::string Effect::move(string dir) {
    return player->move(dir);
}

std::string Effect::movePlayer(string dir) {
    return player->playerMove(dir);
}

std::string Effect::hit(Character *target) {
    return player->hit(target);
}

void Effect::takeHit(int n) {
    return  player->takeHit(n);
}

void Effect::heal(int h) {
    return  player->heal(h);
}
