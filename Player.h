#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <vector>
#include <stdlib.h>

struct Coordinate
{
    int x, y;
    Coordinate(int paramx, int paramy) : x(paramx), y(paramy) {}
};

struct Unit
{
    int mark;
    int length;
    int hits = 0;
    std::vector<Coordinate> coords;
};

class Player
{
        QString name;
        std::vector<int> sank;
        std::vector<Unit> ships;
    public:
        int board[10][10];
        int shots[10][10];
        void initialize_board();
        void debugBoard();
        bool is_a_hit(int,int);
        void create_ships();
        std::vector<Unit> get_ships(){return ships;}
        void set_name(QString);
        QString get_name();
        bool has_lost();
        std::vector<int> get_sank(){return sank;}
    protected:
        Player();

};

#endif
