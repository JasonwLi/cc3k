#ifndef _GAME_H
#define _GAME_H
#include <string>
#include <vector>

class Tile;
class Player;
class Enemy;
class Component;
class Controller;

using namespace std;

class Game{
    private:
        Tile** theFloor;
        int row;
        int column;
        Player *pc;
        int floorLevel;
        vector<Enemy*> enemies;
        vector<Potion*> potions;
        vector<Treasure*> treasures;
        Controller* control;
    public:
        Game(int row, int column);
        ~Game();
        void init(Controller* ctrl);
        void buildFloor();
        void loadFloor(string floorTemp);
        void createFloor();
        void createPC();
        void createStair();
        void createEnemies();
        void createPotions();
        void createTreasures();
        void createFloor();
        void createChambers();
        int getRow();
        int getCol();
        int getLevel();
        Tile* getRandTile();
        Tile* getTile(int row, int col);
        Player* getPC();
        vector<Enemy*> getEnemies();
        vector<Potion*>getPotions();
        vector<Treasure*>getTreasure();
        void clearFloor();
        void setLevel(int num);
        void setPC(Player *p);
        void notify(int row, int col, char ch);
        string attack(string dir);
        string usePotion(string dir);
}; 
