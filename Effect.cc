#include "Effect.h"
using namespace std;

Effect::Effect(int c, Player *player) :Player{player}, change{c}{}
Effect::~Effect() {}

std::string Effect::getRace() { return race;}
int Effect::getAtk() { return Atk;}
int Effect::getDef() { return Def;}
int Effect::getHP() { return HP;}

char Effect::getSymbol(){ return symbol;}
std::string Effect::getName() { return name;}
std::string Effect::getType() { return type;}

int Effect::getMaxHP() { return maxHP;}
unsigned int Effect::getGold() { return gold;}
Player* Effect::getPlayer() { return this;}


void Effect::addGold(int g) {
    gold += g;
    return;
}

void Effect::setGold(int g) {
    gold = g;
    return;
}

void Effect::setAtk(int a) {
    Atk = a;
    return;
}

void Effect::setDef(int d) {
    Def = d;
    return;
}

void Effect::setHP(int h) {
    HP = h;
    return;
}

std::string Effect::move(string dir) {
    return player->move(dir);
}

std::string Effect::movePlayer(string dir) {
    return player->movePlayer(dir);
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
