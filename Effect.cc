#include "Effect.h"
using namespace std;

//constructor takes in the player pointer inside decorator, other fields are set to default
Effect::Effect(int c, Player *player) :Player{player->getMaxHP(), player->getRace(), player->getAtk(),player->getDef(),
                                              player->getHP(), player->getSymbol(), player->getName(), player->getType()},
                                       change{c}, player{player}{}


Effect::~Effect() {}

//all access to fields are set to player pointed by Player*
std::string Effect::getRace() { return player->getRace();}
int Effect::getAtk() { return player->getAtk();}
int Effect::getDef() { return player->getDef();}
int Effect::getHP() { return player->getHP();}

char Effect::getSymbol(){ return player->getSymbol();}
std::string Effect::getName() { return player->getName();}
std::string Effect::getType() { return player->getType();}

int Effect::getMaxHP() { return player->getMaxHP();}
unsigned int Effect::getGold() { return player->getGold();}

Player* Effect::getPlayer() {
    //delete this pointer, return the player* inside the decorator
    //so potion effects are cleaned up
    Player* temp = player->getPlayer();
    delete this;
    return temp;
}


void Effect::addGold(int g) {
    player->addGold(g);
    return;
}

void Effect::setGold(int g) {
    player->setGold(g);
    return;
}

void Effect::setAtk(int a) {
    player->setAtk(a);
    return;
}

void Effect::setDef(int d) {
    player->setDef(d);
    return;
}

void Effect::setHP(int h) {
    player->setHP(h);
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
