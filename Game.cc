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
jason@ubuntu:~/A5$ vi Game.cc
jason@ubuntu:~/A5$ cat Game.cc
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

int getChamber(int x, int y){
    int chNum;
    return chNum;
}
    
void Game::init(string file, Controller* ctrl){
    fstream f(file);
    for(int k = 0; k < row; k++){
        for (int j = 0; k < column; j++){
            char c;
            f >> noskipws >> c;
            int chamber = getChamber(k,j);
            theFloor[k][j] = new Tile(k,j,cham);
            theFloor[k][j].setTile(c, this);
            theFloor[k][j].setNeighbour();
        }
        f.get();
    }
    f.close;
    control = ctrl;
}

void Game::notify(int row, int column, char ch){
    control->notify(row, column, ch);
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

void Game::createTreasures(){
   for (int j = 0; j < 10; j++){
        int rng = rngGen(8);
        Tile *tile = getRandTile();
        Treasure *tr = nullptr;
        if(rng <= 5){
            tr = new NormalHoard();
        }else if (rng < = 7){
            tr = new SmallHourd();
        }else{
            tr = new DragonHoard();
            Dragon* d = tr->getDragon;
            int drng;
            while(true){
                drng = rngGen(8);
                dLocal = Tile->getNeighbour(drng);
                if(isValidTile(dLocal)){
                    d->setLocation(dLocal);
                    dLocal->setComponent(d);
                    break;
                }
            }
        }
        tr->setLocation(tile);
        tile->setComponent(tr);
        treasures.push_back(tr);
    }
}

void Game::setLevel(int num){
    level = num;
}

int Game::getLevel(){
    return level;
}

Tile* Game::getTile(int row, int col){
    Tile *t = &(theFloor[row][col]);
    return t;
}

void Game::setPC(Player* p){
    pc = p;
    return;
}

Player* Game::getPlayer(){
    return pc;
}

vector<Enemy*> Game::getEnemies(){
    return enemies;
}

vector<Potion*> Game::getPotions(){
    return potions;
}

vector<Treasure*> Game::getTreasures(){
    return treasures;
}

int Game::getRow(){
    return row;
}

int Game::getColumn(){
    return column;
}

void Game::clearFloor(){
    if(theFloor){
        for(int j = 0; j < row; j++){
            for(int k = 0; k < column; k++){
                if(theFloor[j][k].getComponent()->getName() = "Dragon"){
                    continue;
                }
                delete theFloor[j][k].getComponent();
                theFloor[j][k].setComponent(nullptr);
            }
        }
    }
    for(int k = 0; k < 20; k++){
        delete enemies.front();
    }
    for(int k = 0; k < 10; k++){
        delete treasures.front();
    }
    for(int k = 0; k < 10; k++){
        delete potions.front();
    }
    if(pc){
        Tile *t = pc->getLocation();
        if(t){
            t->setComponent(nullptr);
        }
        pc->setLocation(nullptr);
    }
}



void Game::buildFloor(){
    clearFloor();
    createPC();
    createStair();
    createPotions();
    createEnemies();
    createTreasures();
    level+=1;
}

void Game::loadFloor(string floorTemp){
    clearFloor();
    stringstream s(floorTemp);
    Dragon *d = nullptr;
    DragonHoard *dh = nullptr;
    for(int j = 0; j <  row; j++){
        for(int k = 0; k < column; k++){
            char c;
            ss >> noskipws >> c;
            if(c == '@'){
                theFloor[i][j].setComponent(pc);
                pc->setLocation(&(theFloor[j][k]));
            }
            else if(c == '\\'){
                Stair* s = new Stair();
                theFloor[j][k].setComponent(s);
                s->setLocation(&(theFloor[j][k]));
            }
            else if(c == '0'){
                Potion* p = new Potion("BD");
                potions.push_back(p);
                theFloor[j][k].setComponent(p);
                p->setLocation(&(theFloor[j][k]));
 
            }
            else if(c == '1'){
                Potion* p = new Potion("WD");
                potions.push_back(p);
                theFloor[j][k].setComponent(p);
                p->setLocation(&(theFloor[j][k]));
 
            }
            else if(c == '2'){
                Potion* p = new Potion("WA");
                potions.push_back(p);
                theFloor[j][k].setComponent(p);
                p->setLocation(&(theFloor[j][k]));
 
            }
            else if(c == '3'){
                Potion* p = new Potion("PH");
                potions.push_back(p);
                theFloor[j][k].setComponent(p);
                p->setLocation(&(theFloor[j][k]));
            }
            else if(c == '4'){
                Potion* p = new Potion("RH");
                 potions.push_back(p);
                theFloor[j][k].setComponent(p);
                p->setLocation(&(theFloor[j][k]));
            }
            else if(c == '5'){
                Potion* p = new Potion("BA");
                potions.push_back(p);
                theFloor[j][k].setComponent(p);
                p->setLocation(&(theFloor[j][k]));
            }
            else if(c == '6'){
                NormalHoard* h = new NormalHoard();

                theFloor[i][j].setObject(h);
                h->setPosition(&(theFloor[i][j]));
            }
            else if(c == 'H'){
                Human* h = new Human();
                enemies.push_back(h);
                theFloor[j][j].setComponent(h);
                h->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'L'){
                Halfling* l = new Halfling();
                enemies.push_back(l)
                theFloor[j][k].setComponent(l);
                l->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'O'){
                Orc* o = new Orc();
                enemies.push_back(o);
                theFloor[j][j].setComponent(o);
                o->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'M'){
                Merchant* m = new Merchant();
                enemies.push_back(m)
                theFloor[j][k].setComponent(m);
                m->setLocation(&(theFloor[j][k]));

            }
            else if(c == 'W'){
                Dwarf* w = new Dwarf();
                enemies.push_back(w)
                theFloor[j][k].setComponent(w);
                w->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'E'){
                Elf* e = new Elf();
                enemies.push_back(e)
                theFloor[j][k].setComponent(e);
                e->setLocation(&(theFloor[j][k]));

            }
            else if(c == '7'){
                SmallHoard* sh = new SmallHoard();
                treasures.push_back(sh);
                theFloor[j][k].setComponent(sh);
                sh->setLocation(&(theFloor[j][k]));
            }
            else if(c == '8'){
                MerchantHoard* mh = new MerchantHoard();
                treasures.push_back(mh);
                theFloor[j][j].setObject(mh);
                mh->setPosition(&(theFloor[j][k]));
            }
            
            else if(c == '9'){
                DragonHoard* dht = new DragonHoard(d);
                if(d){
                    d->setHoard(dht);
                    d = nullptr;
                }
                else{
                    dh = dht;
                }
                theFloor[j][k].setObject(dht);
                h->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'D'){
                Dragon* dt = new Dragon(dh);
                if(dh){
                    dh->setDragon(dt);
                    dh = NULL;
                }
                else{
                    d = dt;
                }
                theFloor[j][k].setObject(d);
                d->setLocation(&(theFloor[j][k]));
            }

        }
        s.get();
    }
}

string Game::Attack(string dir){
    
}

string Game::usePotion(string dir){
}
