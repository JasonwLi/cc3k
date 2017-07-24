#ifndef _TILE_H
#define _TILE_H

#include "game.h"

using namespace std;

class Component;
class Game;

class Tile {
    private:
        int row;
        int column;
        int chamberNum;
        char ch;
        Game *game;
        Tile *neighbours[8];
        Component *component;
    public:
        Tile();
        ~Tile();
        Component* getComponent();
        int getRow();
        int getColumn();
        char getCh();
        int getChamber();
        void notify(int row, int col, char ch);
        void setComponent(Component *comp);
        void setNeighbours();
        void setTile(int x, int y, char c, int chamber, Game *g);
        Tile *getNeighbour(int num);
        Tile *getNeighbours();
};

#endif
