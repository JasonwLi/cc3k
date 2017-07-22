#include "Component.h"
#include "Tile.h"
#include <iostream>

Tile::Tile(): row(0), column(0), ch(' '), chamber(0){
    for(int j = 0; j < 8; j++){
        neighbours[j] = NULL;
    }
    game = NULL:
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
    else{
        notify(row, column, ch);
    }
}

void Tile::setNeighbours(){
    int cp = column+1;
    int rp = row+1;
    int cm = column-1;
    int rm = row-1;
    if(cp < 80 && rp < 25 && rm > 1 && cm > 1){
        neighbours = game->getTile(rm, column);
        neighbours = game->getTile(row, cm);
        neighbours = game->getTile(rp, column);
        neighbours = game->getTile(row, cp);
        neighbours = game->getTile(rp, cm);
        neighbours = game->getTile(rp, cp);
        neighbours = game->getTile(rm, cm);
        neighbours = game->getTile(rm, cp);
    }
}

void Tile::setTile(int x, int y, char c, int chamber, Game *g){
    column = y;
    row = x;
    this.chamber = chamber;
    game = g;
    notify(row, column, ch);
}

Tile* Tile::getNeighbour(int num){
    return neighbours[n];
}

Tile** Tile::getNeighbours(){
    return neighbours;
}

