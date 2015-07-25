#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include "Human.h"

class Computer: public Player
{
        int has_sank = 0;
        bool on_hit = false;
        Coordinate last_hit = Coordinate(0,0);
    public:
        void ai_place_ships();
        bool place_it(Unit);
        void take_turn(Player *enemy);
        Computer()
            : Player()
        {
            ai_place_ships();
        }
};

#endif
