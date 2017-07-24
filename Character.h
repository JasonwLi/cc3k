#ifndef PROJECT_CHARACTER_H
#define PROJECT_CHARACTER_H

#include <string>
#include "Component.h"

class Character: public Object {
protected:
    const std::string race;
    int Atk;
    int Def;
    int HP;
    /*unsigned int maxHP;
    unsigned int baseAtk;
    unsigned int baseDef;*/
public:
    Character(std::string race, int Atk, int Def, int HP, char symbol, string name, string type);
    virtual ~Character() = 0;

    virtual std::string getRace();
    virtual int getAtk();
    virtual int getDef();
    virtual int getHP();
    virtual char getSymbol();
    virtual std::string getName();
    virtual std::string getType();

    virtual void setAtk(int a);
    virtual void setDef(int d);
    virtual void setHP(int h);

    virtual std::string move(string dir);
    virtual std::string hit(Character* target);
    virtual void takeHit(int n);
    virtual void heal(int n);
};




#endif //PROJECT_CHARACTER_H
