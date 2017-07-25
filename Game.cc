#include "Game.h"
#include "Tile.h"
#include "Controller.h"
#include "Component.h"
#include "Stair.h"
#include "Player.h"
#include "Enemy.h"
#include "Potion.h"
#include "Treasure.h"
#include "Effectdeco.h"
#include "Effect.h"
#include <fstream>
#include <sstream>

using namespace std;

class Stairs;
class DragonHoard;

Game::Game(int row, int column):row(row), column(column){
    floorLevel = 0;
    pc = nullptr;
    control = nullptr;
    theFloor = nullptr;
    for (int i = 0; i < 20; i++){
        enemies.push_back(nullptr);
    }
}

Game::~Game(){
    clearFloor();
    delete pc;
    if(theFloor != nullptr){
        for(int i = 0; i < row; i++){
            delete [] theFloor[i];
        }
        delete [] theFloor;
    }
}

bool isValidTile(Tile* t){
    if(t && t->getCh() == '.' && !t->getComponent()){
        return true;
    }
    return false;
}

int getChamber(int row, int col){
    if(col >= 3 && col <= 28 && row >= 3 && row <= 6){
        return 1;
    }
    if((col >= 39 && col <= 61 && row >= 3 && row <= 6)  ||
       (col >= 61 && col <= 75 && row >= 7 && row <= 13) ||
       (col >= 62 && col <= 69 && row == 5)              ||
       (col >= 62 && col <= 72 && row == 6)){
        return 2;
    }
    if(col >= 38 && col <= 50 && row >= 10 && row <= 12){
        return 3;
    }
    if(col >= 4 && col <= 24 && row >= 15 && row <= 21){
        return 4;
    }
    if((col >= 37 && col <= 75 && row >= 19 && row <= 21) ||
       (col >= 65 && col <= 75 && row >= 16 && row <= 18)){
        return 5;
    }
    return 0;
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
    

int rngGen(int chance){
    return rand()%chance+1;
}
    
void Game::init(string file, Controller* ctrl){
    fstream f(file);
    control = ctrl;
    theFloor = new Tile*[row];
    for(int z = 0; z < row; z++){
        theFloor[z] = new Tile[column];
    }
    for(int k = 0; k < row; k++){
        for (int j = 0; j < column; j++){
            char c;
            f >> noskipws >> c;
            int cham = getChamber(k,j);
            theFloor[k][j].setTile(k,j,c,cham, this);
            theFloor[k][j].setNeighbours();
        }
        f.get();
    }
    f.close();
}

void Game::notify(int row, int column, char ch){
    control->notify(row, column, ch);
}     

void Game::createPC(){
    int c = rngGen(5);
    Tile *tile;
    while(true){
        tile = getRandTile();
        if(tile->getChamber() == c){
            break;
        }
    }
    pc->setLocation(tile);
    tile->setComponent(pc);
}

void Game::createStairs(){
    Tile *tile;
    while(true){
        tile = getRandTile();
        if(pc->getLocation()->getChamber() != tile->getChamber()){
            break;
        }
    }
    Stairs *s = new Stairs();
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
        if (rng == 2){
            p = new Potion("WD");
            return;
        }
        if (rng == 3){
            p = new Potion("WA");
            return;
        }
        if (rng == 4){
            p = new Potion("PH");
            return;
        }
        if (rng == 5){
            p = new Potion("RH");
            return;
        }
        if (rng == 6){
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
        }else if (rng <= 7){
            tr = new SmallHoard();
        }else{
            tr = new DragonHoard();
            Dragon* d = tr->getDragon();
            Tile *dLocal;
            int drng;
            while(true){
                drng = rngGen(8);
                dLocal = tile->getNeighbour(drng);
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
    floorLevel = num;
}

int Game::getLevel(){
    return floorLevel;
}

Tile* Game::getTile(int row, int col){
    Tile *t = &(theFloor[row][col]);
    return t;
}

void Game::setPC(Player* p){
    pc = p;
}

Player* Game::getPC(){
    return pc;
}

vector<Enemy*> Game::getEnemies(){
    return enemies;
}

vector<Potion*> Game::getPotions(){
    return potions;
}

vector<Treasure*> Game::getTreasure(){
    return treasures;
}

int Game::getRow(){
    return row;
}

int Game::getCol(){
    return column;
}

void Game::clearFloor(){
    if(theFloor){
        for(int j = 0; j < row; j++){
            for(int k = 0; k < column; k++){
                if(theFloor[j][k].getComponent()->getName() == "Dragon"){
                    continue;
                }
                delete theFloor[j][k].getComponent();
                theFloor[j][k].setComponent(nullptr);
            }
        }
    }
    while(!enemies.empty()){
         enemies.pop_back();
    }
    while(!treasures.empty()){
         treasures.pop_back();
    }
    while(!potions.empty()){
        potions.pop_back();
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
    createStairs();
    createPotions();
    createEnemies();
    createTreasures();
    floorLevel+=1;
}

void Game::loadFloor(string floorTemp){
    clearFloor();
    stringstream s(floorTemp);
    Dragon *d = nullptr;
    DragonHoard *dh = nullptr;
    for(int j = 0; j <  row; j++){
        for(int k = 0; k < column; k++){
            char c;
            s >> noskipws >> c;
            if(c == '@'){
                theFloor[j][k].setComponent(pc);
                pc->setLocation(&(theFloor[j][k]));
            }
            else if(c == '\\'){
                Stairs* s = new Stairs();
                theFloor[j][k].setComponent(s);
                s->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'H'){
                Human* h = new Human();
                enemies.push_back(h);
                theFloor[j][k].setComponent(h);
                h->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'O'){
                Orc* o = new Orc();
                enemies.push_back(o);
                theFloor[j][k].setComponent(o);
                o->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'L'){
                Halfling* l = new Halfling();
                enemies.push_back(l);
                theFloor[j][k].setComponent(l);
                l->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'M'){
                Merchant* m = new Merchant();
                enemies.push_back(m);
                theFloor[j][k].setComponent(m);
                m->setLocation(&(theFloor[j][k]));

            }
            else if(c == 'E'){
                Elf* e = new Elf();
                enemies.push_back(e);
                theFloor[j][k].setComponent(e);
                e->setLocation(&(theFloor[j][k]));

            }
            else if(c == 'W'){
                Dwarf* w = new Dwarf();
                enemies.push_back(w);
                theFloor[j][k].setComponent(w);
                w->setLocation(&(theFloor[j][k]));
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

                theFloor[j][k].setComponent(h);
                h->setLocation(&(theFloor[j][k]));
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
                theFloor[j][k].setComponent(mh);
                mh->setLocation(&(theFloor[j][k]));
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
                theFloor[j][k].setComponent(dht);
                dht->setLocation(&(theFloor[j][k]));
            }
            else if(c == 'D'){
                Dragon* dt = new Dragon(dh);
                if(dh){
                    dh->setDragon(dt);
                    dh = nullptr;
                }
                else{
                    d = dt;
                }
                theFloor[j][k].setComponent(d);
                d->setLocation(&(theFloor[j][k]));
            }

        }
        s.get();
    }
}

string Game::attack(string dir){
    int dnum;
    if(dir == "no"){
        dnum = 0;
    }else if(dir == "we"){
        dnum = 1;
    }else if(dir == "so"){  
        dnum = 2;
    }else if(dir == "ea"){  
        dnum = 3;
    }else if(dir == "nw"){  
        dnum = 4;
    }else if(dir == "ne"){  
        dnum = 5;
    }else if(dir == "sw"){  
        dnum = 6;
    }else if(dir == "se"){  
        dnum = 7;
    }
    Tile* dest = pc->getLocation()->getNeighbour(dnum);
    Component* comp = dest->getComponent();
    
    string outmsg = "";
    if(comp && comp->getType() == "enemy"){
        Enemy* monster = static_cast<Enemy*>(comp);
        outmsg += pc->hit(monster);
        // if dragon is killed delete it from its hoard.
        if(monster->getName() == "Dragon" && monster->getHP() < 1){
            static_cast<Dragon*>(monster)->getHoard()->slayDragon();
        }
    }
    else{
        outmsg += "There is no enemy in that directioN!";
    }
    return outmsg;
}

string Game::usePotion(string dir){
    int dnum;
    if(dir == "no"){
        dnum = 0;
    }else if(dir == "we"){
        dnum = 1;
    }else if(dir == "so"){
        dnum = 2;
    }else if(dir == "ea"){
        dnum = 3;
    }else if(dir == "nw"){
        dnum = 4;
    }else if(dir == "ne"){
        dnum = 5;
    }else if(dir == "sw"){
        dnum = 6;
    }else if(dir == "se"){ 
        dnum = 7;
    }
    Tile* dest = pc->getLocation()->getNeighbour(dnum);
    Component *comp = dest->getComponent();

    string outmsg = "";

    if(!comp || comp->getType() != "potion"){
        return "No potion exists on the" + dir +" tile.";
    }
    else{
        Potion* p = static_cast<Potion*>(comp);

        if(p->getEffect() == "RH"){
            int num = 10;
            if(pc->getRace() == "Drow"){
                    num = num*1.5;
            }
            pc->heal(num);
            outmsg += "used a health potion from " + dir +" healed " + to_string(num) + " Health. ";

        }
        else if(p->getEffect() == "PH"){
            int num = 10;
            if(pc->getRace() == "Drow"){
                    num = num*1.5;
            }
            pc->takeHit(num);
            outmsg += "used a poison potion from " + dir +" lost " + to_string(num) + " Health. ";
        }
        else if(p->getEffect() == "BA"){
            int num = 5;
            if(pc->getRace() == "Drow"){
                    num = num*1.5;
            }
            pc = new boostAtk(num, pc);
            outmsg += "used a damage boost potion from " + dir +"  gain " + to_string(num) + " Attack power. ";
        }
        else if(p->getEffect() == "WA"){
            int num = 5;
            if(pc->getRace() == "Drow"){
                    num = num*1.5;
            }           
            pc = new boostAtk(-num, pc);
            outmsg += "used a damage wound potion from " + dir +" lost " + to_string(num) + " Attack power. ";
        }
        else if(p->getEffect() == "BD"){
            int num = 5;
            if(pc->getRace() == "Drow"){
                    num = num*1.5;
            }           
            pc = new boostDef(num, pc);
            outmsg += "used a defence boost potion from " + dir +" gain " + to_string(num) + " Defense power ";
        }
        else if(p->getEffect() == "WD"){
            int num = 5;
            if(pc->getRace() == "Drow"){
                    num = num*1.5;
            }           
            pc = new boostDef(-num, pc);
            outmsg += "used a defence wound potion from " + dir +" lost " + to_string(num) + " Defense power";
        }
        p->getLocation()->setComponent(nullptr);
        delete p;
        return outmsg;
    }
}
