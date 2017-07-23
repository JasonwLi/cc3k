#include "Game.h"
#include "Tile.h"
#include "Controller.h"
#include "Component.h"
#include "Stair.h"
#include "Player.h"
#include "Enemy.h"
#include "Potion.h"
#include "Treasure.h"
#include "Effects.h"
#include <fstream>
#include <sstream>

using namespace std;

class Stair;
class DragonHoard;

Game::Game(int row, int column):level(0),row(row), columne(column){
    pc = NULL;
    control = NULL;
    theFloor = NULL:
    for (int i = 0; i < 20; i++){
        enemies[i] = NULL;
    }
}

Game::~Game(){
    clearFloor();
    delete pc;
    if(theFloor != NULL){
        for(int i = 0; i < row; i++){
            delete [] theFloor[i];
        }
        delete [] theFloor;
    }
}

Tile* Game::getRandTile(){
    int x = rand()%row;
    int y = rand()%column;
    Tile *t = getTile(x,y);
    return t;
}
    
    

bool isValidTile(Tile* t){
    if(t && t->getCh() == "." && !t->getComponent()){
        return true;
    }
    return false;
}

int rngGen(int chance){
    return rand()%chance+1;
}
    
void Game::init(string file, Controller* ctrl){
}    
    

void Game::createPC(){
    int c = rngGen(5);
    while(true){
        Tile *tile = getRandTile();
        if(isValidTile(tile)){
            break;
        }
    }
    pc->setLocation(tile);
    Tile->setComponent(pc);
}

void Game::createStair(){
    while(true){
        Tile *tile = getRandTile();
        if(isValidTile(tile) && pc->getLocation()->getChamber != tile->getChamber){
            break;
        }
    }
    Stair *s = new Stair();
    s->setLocation(tile);
    tile->setComponent(s);
}

void Game::createEnemies(){
    for(int i = 0; i < 20; i++){    
        int rng = rngGen(18);
        Enemy *e = nullptr;
        while(true){
            Tile *tile = getRandTile();
            if(isValidTile(tile)){
                break;
            }
        }
        if(rng < 4){
            e = new Human();
        }else if(rng < 7){
            e = new Dwarf();
        }else if(rng < 12){
            e = new Halfling();
        }else if(rng < 14){
            e = new Elf();
        }else if(rng < 16){
            e = new Orc();
        }else if(rng < 18){
            e = new Merchant();
        }
        enemies.push_back(e);
        tile->setComponent(e);
        e->setLocation(tile);
    }
}
