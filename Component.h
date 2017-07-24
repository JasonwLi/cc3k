#ifndef _COMPONENT_H
#define _COMPONENT_H
#include <string>
#include <iostream>

class Tile;

class Component{
    const char symbol;
    const std::string name;
    const std::string type;
    Tile* location;
    public:
        Component(char symbol, std::string name, std::string type);
        virtual ~Component() = 0;
        virtual char getSymbol();
        virtual Tile* getLocation();
        virtual std::string getName();
        virtual std::string getType();
        virtual void setLocation(Tile *loc);
};

#endif 
