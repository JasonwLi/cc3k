#include "Component.h"
#include "Tile.h"
#include <string>
#include <iostream>

using namespace std;

Component::Component(char symbol, string name, string type): symbol(symbol), name(name), type(type){
    location = NULL;
}

Component::~Component(){}

string Component::getName(){
    return name;
}

string Component::getType(){
    return type;
}

char Component::getSymbol(){
    return symbol;
}

Tile* Component::getLocation(){
    return location;
}

void Component::setLocation(Tile* loc){
    location = loc;
}
