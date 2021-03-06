#ifndef PROJECT_EFFECT_H
#define PROJECT_EFFECT_H

#include "Player.h"
#include <string>

class Effect:public Player{
protected:
    int change;
    Player* player;

public:
    Effect(int c, Player *player);
    virtual ~Effect();

    std::string getRace();
    int getAtk();
    int getDef();
    int getHP();
    char getSymbol();
    std::string getName();
    std::string getType();
    int getMaxHP();
    unsigned int getGold();
    Player* getPlayer();
    void addGold(int g);
    void setGold(int g);

    void setAtk(int a);
    void setDef(int d);
    void setHP(int h);

    std::string move(std::string dir);
    std::string movePlayer(std::string dir);
    std::string hit(Character* target);
    void takeHit(int n);
    void heal(int h);
};
#endif //PROJECT_EFFECT_H
