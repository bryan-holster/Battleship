#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "Computer.h"
#include "Ship.h"
#include <QList>

class Human: public Player
{
        int has_sank = 0;
        bool on_hit = false;

    public:
        void setShips(QList<Ship*>);
        void take_turn(Player *enemy, int x, int y);
        Human()
            : Player()
        {
        }
};

#endif // HUMAN_H
