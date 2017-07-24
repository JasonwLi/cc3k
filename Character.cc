#include <iostream>
#include <sstream>
#include <cmath>
#include "Tile.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Treasure.h"

using namespace std;

Character::Character(std::string race, int Atk, int Def, int HP, char symbol, string name, string type):
        Component(symbol, name, type), race{race}, Atk{Atk}, Def{Def}, HP{HP} {}

Character::~Character() {}

//return stats of Character
std::string Character::getRace() {return race;}
int Character::getAtk() {return Atk;}
int Character::getDef() {return Def;}
int Character::getHP() {return HP;}

//set stats of Character
void Character::setAtk(int a) {
    Atk = a;
    return;
}

void Character::setDef(int d) {
    Def = d;
    return;
}

void Character::setHP(int h) {
    HP = h;
    return;
}

//Move
std::string Character::move(string dir) {
    std::string outbox = "";
    Tile* curr = this->getLocation();
    Tile* dest;
    if (dir == "no") dest = curr->getNeighbour(0);
    else if (dir == "we") dest = curr->getNeighbour(1);
    else if (dir == "so") dest = curr->getNeighbour(2);
    else if (dir == "ea") dest = curr->getNeighbour(3);
    else if (dir == "nw") dest = curr->getNeighbour(4);
    else if (dir == "ne") dest = curr->getNeighbour(5);
    else if (dir == "sw") dest = curr->getNeighbour(6);
    else if (dir == "se") dest = curr->getNeighbour(7);
    char destCh = dest->getCh();
    Component* destComp = dest->getComponent();
    if (type != "player") {
        if (destComp || destCh!='.') return "Blocked";
        //if type not player, dest is available, move outside the if-statment
    }else{ //type == "player"
        if(destComp){ //if there is something at the dest
            if (destComp->getType() == "stair") {
                return "Moved to the next floor";
            }else if(destComp->getType() == "treasure"){
                //treasure at the dest, we need to verify if it has a dragon
                if(static_cast<Treasure*>(destComp)->getDragon()){ //force treat Comp at dest as Treasure
                    //if not NULL, treasure still as dragon guarding it
                    return "Dragon Hoard guarded by Dragon";
                }else{
                    //if NULL, its a hoard from either slain dragon or slain merchant, both can be picked up
                    int pickGold = static_cast<Treasure*>(destComp)->getValue();
                    Player *currInstance = static_cast<Player*>(this);
                    currInstance->addGold(pickGold);
                    string amt = std::to_string(pickGold);
                    outbox += amt;
                    delete destComp; //since the hoard has already been picked up
                }
            }else if(destCh == '|' || destCh == ' ' || destCh == '-') {
                return "Cannot get there";
            }else if(destComp->getType() == "potion"){
                return "Blocked by potion";
            }else { //blocked by something else, should be enemy
                return "Blocked by " + destComp->getRace();
            }
        }else{  //nothing's blocking the way of player
            outbox += "Player moved";
        }
    }
    curr->setComponent(nullptr);
    this->setLocation(dest);
    dest->setComponent(this);
    return outbox;
}

std::string Character::hit(Character *target) {
    string outbox = "";
    string sourceType = this->getType();
    string targetType = target->getType();
    string sourceRace = this->getRace();
    string targetRace = target->getRace();
    double atkStat = getAtk();
    double defStat = getDef();
    int damage = ceil(100 / (100+defStat) * atkStat);
    if (sourceRace == "Orc" && targetRace == "Goblin") damage = ceil(150 / (100+defStat) * atkStat);
    //bool hitTarget = false;
    int hpLeft;
    int atkRounds = 1;
    int missFactor = 1; //1 will lead to always miss, 2 will lead to 50% miss
    if (targetRace == "Halfling" || targetType == "player") missFactor = 2;
    if (targetRace != "Drow" && sourceRace == "Elf") atkRounds = 2;
    for(int i = 0; i<atkRounds; i++){
        int miss = rand() % missFactor;
        if (miss == 1) {
            if (sourceType == "player"){
                outbox += "Missed attack from player to " + targetRace;
            }else{
                outbox += "Missed attack to player from " + sourceRace;
            }
        }else{ //did not miss
            target->takeHit(damage);
            hpLeft = target->getHP();
            if (hpLeft <= 0){
                if(sourceType == "player"){
                    outbox += targetRace + " is slain by the player. ";
                    break;
                }else{
                    outbox += " The Player is killed by the attack from " + sourceRace;
                    break;
                }
            }
            if (sourceType == "player") {
                outbox = "Player dealt " + std::to_string(damage) + " to " + targetRace;
                if (sourceRace == "Vampire") {
                    if (targetRace == "Dwarf") {
                        takeHit(5);
                        outbox += " Vamp's allergic to Dwarf Blood, -5 hp. ";
                        int playerHP = this->getHP();
                        if (playerHP <= 0){
                            outbox += "Player(vamp) is killed by allergy... ";
                        }
                    } else {
                        heal(5);
                        outbox += " Vamp healed 5 hp from attack. ";
                    }
                }
                if (defRace == "Merchant") {
                    Merchant::hostile == true;
                }
            }
        }
    }
    return outbox;
}

void Character::takeHit(int n) {
    if (this->HP > n){
        HP -= n;
    }else{
        HP = 0;
    }
    return;
}

void Character::heal(int n) {return;}

