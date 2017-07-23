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
    while(true){
        int x = rand()%row;
        int y = rand()%column;
        Tile *t = getTile(x,y);
        if(isValidTile(t)){
            return t;
        }
    }
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
        if(tile->getChamber == c){
            break;
        }
    }
    pc->setLocation(tile);
    Tile->setComponent(pc);
}

void Game::createStair(){
    while(true){
        Tile *tile = getRandTile();
        if(pc->getLocation()->getChamber != tile->getChamber){
            break;
        }
    }
    Stair *s = new Stair();
    s->setLocation(tile);
    tile->setComponent(s);
}

void Game::createEnemies(){
    for(int i = 0; i < 20; i++){    
        Tile *tile = getRandTile();
        int rng = rngGen(18);
        Enemy *e = nullptr;
        if(rng <= 4 && rng >= 1){
            e = new Human();
        }else if(rng >=5 && rng <= 7){
            e = new Dwarf();
        }else if(rng >= 8 && rng <= 12){
            e = new Halfling();
        }else if(rng >= 13 && rng <= 14){
            e = new Elf();
        }else if(rng >= 15 && rng <= 16){
            e = new Orc();
        }else if(rng >= 17 && rng <= 18){
            e = new Merchant();
        }
        enemies.push_back(e);
        tile->setComponent(e);
        e->setLocation(tile);
    }
}

void Game::createPotions(){
    for(int i = 0; i < 10; i++){
        Tile *tile = getRandTile();
        int rng = rngGen(6);
        Potion *p = nullptr;
        if (rng == 1){
            p = new Potion("BD");
            return;
        }
        if (rng = 2){
            p = new Potion("WD");
            return;
        }
        if (rng = 3){
            p = new Potion("WA");
            return;
        }
        if (rng = 4){
            p = new Potion("PH");
            return;
        }
        if (rng = 5){
            p = new Potion("RH");
            return;
        }
        if (rng = 6){
            p = new Potion("BA");
            return;
        }
        potions.push_back(p);
        p->setLocation(tile);
        tile->setComponent(p);
    }
}

void Game::createTreasure(){
}

