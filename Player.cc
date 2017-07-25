#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

Player::Player(int maxHP, std::string race, int Atk, int Def, int HP, char symbol, string name, string type) :
        Character(race, Atk, Def, HP, symbol,name, type), gold{gold}, maxHP{maxHP} {}

Player::~Player() {}

int Player::getMaxHP() {
    return  maxHP;
}

unsigned int Player::getGold() {
    return gold;
}

Player* Player::getPlayer() {
    return this;
}

void Player::addGold(int g) {
    gold += g;
    return;
}

void Player::setGold(int g) {
    gold = g;
    return;
}

void Player::heal(int h) {
    if ((HP + h) > maxHP){
        HP = maxHP;
    }else{
        HP += h;
    }
    return;
}

Player::Player(Player *other) : 
Character(other->getRace(), other->getAtk(), other->getDef(), other->getHP(), 
          other->getSymbol(), other->getName(), other->getType()), 
gold{other->getGold()}, maxHP{other->getMaxHP()}{}

std::string Player::movePlayer(std::string dir) {
    string msg = "";
    msg += move(dir);
    return  msg;
}

Shade::Shade() :Player(125,"Shade",25,25,125,'@',"Shade","player"){}
Shade::~Shade() {}

Drow::Drow() :Player(125,"Drow",25,15,150,'@',"Drow","player"){}
Drow::~Drow() {}

Vampire::Vampire() :Player(50,"Vampire",25,25,50,'@',"Vampire","player"){}
Vampire::~Vampire() {}
void Vampire::heal(int h) {
    HP += h;
}

Troll::Troll() :Player(120,"Troll",25,15,120,'@',"Troll","player"){}
Troll::~Troll() {}

Goblin::Goblin() :Player(110,"Goblin",15,20,110,'@',"Goblin","player"){}
Goblin::~Goblin() {}

