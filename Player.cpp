#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Game.h"
#include <QDebug>

using namespace std;

extern Game* game;

Player::Player(void)
{
    initialize_board();
    create_ships();
}

void Player::initialize_board() //Creates a 10x10 board
{
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            board[i][j] = 0;
            shots[i][j] = 0;
        }
    }
}

void Player::debugBoard()
{
    for(int i=0;i<10;i++){
        qDebug() << board[i][0] << board[i][1] << board[i][2] << board[i][3] << board[i][4] << board[i][5] << board[i][6] << board[i][7] << board[i][8] << board[i][9];
    }
}

bool Player::is_a_hit(int x,int y)
{
    qDebug() << QString("Checking if it was a hit");
    if(board[x][y] != 0 && board[x][y] != 6)
    {
        for (unsigned i=0;i<ships.size();i++)
        {
            if(board[x][y] == ships.at(i).mark)
            {
                ships.at(i).hits += 1;
                if(ships.at(i).hits==ships.at(i).length)
                {
                    sank.push_back(ships.at(i).mark);
                }
            }
        }
        return true;
    }
    board[x][y] = 6;
    return false;
}

void Player::set_name(QString name)
{
    this->name = name;
}

QString Player::get_name()
{
    return name;
}

bool Player::has_lost()
{
    if(sank.size() == 5)
    {
        //qDebug() << this->name << QString("has lost");
        return true;
    }
    return false;
}

void Player::create_ships() //Creates the 5 ships and returns them in a vector
{
    Unit carrier; carrier.length=5; carrier.mark = 1;
    Unit battleship; battleship.length=4; battleship.mark = 2;
    Unit cruiser; cruiser.length=3; cruiser.mark = 3;
    Unit submarine; submarine.length=3; submarine.mark = 4;
    Unit destroyer; destroyer.length=2; destroyer.mark = 5;

    vector<Unit> ships;
    ships.push_back(carrier);
    ships.push_back(battleship);
    ships.push_back(cruiser);
    ships.push_back(submarine);
    ships.push_back(destroyer);

    this->ships = ships;
}



