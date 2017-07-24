#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <string>
#include "Character.h"

class Player: public Character{
protected:
    unsigned int gold;
    const int maxHP;

public:
    Player(int maxHP, std::string race, int Atk, int Def, int HP, char symbol, string name, string type);
    virtual ~Player() = 0;
    virtual int getMaxHP();
    virtual int getGold();
    virtual Player* getPlayer();
    virtual void addGold(int g);
    virtual void setGold(int g);
    virtual void heal(int h);
    virtual std::string movePlayer(std::string dir);
};

class Shade : public Player{
public:
    Shade();
    ~Shade();
};

class Drow : public Player{
public:
    Drow();
    ~Drow();
};

class Vampire : public Player{
public:
    Vampire();
    ~Vampire();
};

class Troll : public Player{
public:
    Troll();
    ~Troll();
};

class Goblin : public Player{
public:
    Goblin();
    ~Goblin();
};

#endif //PROJECT_PLAYER_H
