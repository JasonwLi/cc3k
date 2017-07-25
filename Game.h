#ifndef _GAME_H
#define _GAME_H
#include <string>
#include <vector>

class Tile;
class Player;
class Enemy;
class Component;
class Controller;
class Potion;
class Treasure;

class Game{
    private:
        Tile** theFloor;
        int row;
        int column;
        Player *pc;
        int floorLevel;
        std::vector<Enemy*> enemies;
        std::vector<Potion*> potions;
        std::vector<Treasure*> treasures;
        Controller* control;
    public:
        Game(int row, int column);
        ~Game();
        void init(string file, Controller* ctrl);
        void buildFloor();
        void loadFloor(std::string floorTemp);
        void createFloor();
        void createPC();
        void createStairs();
        void createEnemies();
        void createPotions();
        void createTreasures();
        void createChambers();
        int getRow();
        int getCol();
        int getLevel();
        Tile* getRandTile();
        Tile* getTile(int row, int col);
        Player* getPC();
        std::vector<Enemy*> getEnemies();
        std::vector<Potion*> getPotions();
        std::vector<Treasure*> getTreasure();
        void clearFloor();
        void setLevel(int num);
        void setPC(Player *p);
        void notify(int row, int col, char ch);
        std::string attack(std::string dir);
        std::string usePotion(std::string dir);
}; 

#endif
