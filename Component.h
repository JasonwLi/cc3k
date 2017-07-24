#ifndef _COMPONENT_H
#define _COMPONENT_H
#include <string>
#include <iostream>

using namespace std;

class Tile;

class Component{
    const char symbol;
    const string name;
    const string type;
    Tile* location
    public:
        Component(char symbol, string name, string type);
        virtual ~Component() = 0;
        virtual char getSymbol();
        virtual Tile *getLocation();
        virtual string getName();
        virtual string getType();
        virtual void setLocation(Tile *loc);
};

#endif 
