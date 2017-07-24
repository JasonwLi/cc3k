#include "Component.h"
#include "Tile.h"
#include <iostream>

Tile::Tile(int x, int y, int cham): row(x), column(y), ch(' '), chamber(cham){
    for(int j = 0; j < 8; j++){
        neighbours[j] = NULL;
    }
    game = NULL;
    component = NULL;
}

Tile::~Tile(){};

Component* Tile::getComponent(){
    return component;
}

void Tile::getRow(){
    return row;
}

void Tile::getColumn(){
    return column;
}

void Tile::getCh(){
    return ch;
}

int Tile::getChamber(){
    return chamberNum;
}

void Tile::notify(int row, int col, char ch){
    game->notify(row, column, ch);
}

void Tile::setComponent(Component *comp){
    component = comp;
    if(component){
        sym = comp->getChar();
        notify(row, column, sym);
    }else{
        notify(row, column, ch);
    }
}

void Tile::setNeighbours(){
    int cp = column+1;
    int rp = row+1;
    int cm = column-1;
    int rm = row-1;
    if(cp < 80 && rp < 25 && rm > 1 && cm > 1){
        neighbours[0] = game->getTile(rm, column);
        neighbours[1] = game->getTile(row, cm);
        neighbours[2] = game->getTile(rp, column);
        neighbours[3] = game->getTile(row, cp);
        neighbours[4] = game->getTile(rp, cm);
        neighbours[5] = game->getTile(rp, cp);
        neighbours[6] = game->getTile(rm, cm);
        neighbours[7] = game->getTile(rm, cp);
    }
}

void Tile::setTile(char c, Game *g){
    ch = c;
    game = g;
    notify(row, column, ch);
}

Tile* Tile::getNeighbour(int num){
    return neighbours[n];
}

Tile** Tile::getNeighbours(){
    return neighbours;
}

