#ifndef PROJECT_ENEMY_H
#define PROJECT_ENEMY_H

#include "Character.h"
#include <string>

class Enemy:public Character{
private:
    bool active;

public:
    Enemy(std::string race, int Atk, int Def, int HP, char symbol, string name, string type);
    virtual ~Enemy()=0;

    bool ifActive();
    void setActive();
    void setInactive();
    virtual void dropGold();
};

class DragonHoard;

class Human:public Enemy{
public:
    Human();
    ~Human();
    void dropHoard();
};

class Dwarf:public Enemy{
public:
    Dwarf();
    ~Dwarf();
};

class Elf:public Enemy{
public:
    Elf();
    ~Elf();
};

class Orc:public Enemy{
public:
    Orc();
    ~Orc();
};

class Merchant:public Enemy{
private:
    static bool hostile;
public:
    isHostile();
    setHostile();
    Merchant();
    ~Merchant();
    void dropHoard();
};

class Halfling:public Enemy{
public:
    Halfling();
    ~Halfling();
};

class Dragon:public Enemy{
private:
    DragonHoard *dHoard;
public:
    Dragon();
    Dragon(DragonHoard* dHoard);
    ~Dragon();
    void dropHoard();
    DragonHoard* getHoard();
    void setHoard(DragonHoard* dHoard);
};


#endif //PROJECT_ENEMY_H
