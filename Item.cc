#include <string>
#include <iostream>
#include "Item.h"

using namespace std;

Item::Item(string type, string name, char symbol) : Component(symbol, name,type) {}

Item::~Item() {}