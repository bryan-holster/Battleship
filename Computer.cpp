#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include "Game.h"
#include "Computer.h"
using namespace std;

extern Game* game;

struct reorder {
  bool operator() (int i,int j) { return (i<j);}
} s_to_l;

void Computer::ai_place_ships() //Takes a vector of ships and and makes the call to place each ship randomly (for computer)
{
    //qDebug() << board[0][0];
    vector<Unit> ships = get_ships();
    for(unsigned i=0; i<ships.size(); i++)
    {
        while(place_it(ships.at(i)) != true);
    }

    return;
}

bool Computer::place_it(Unit ship) //Takes a single ship and places it randomly on the 10x10 board
{
    int lati, longi;
    vector<int> spaces;
    while(board[lati = rand() % 10][longi = rand() % 10] != 0); //Selects a random empty starting point to place the ship

    int position;
    bool chosen = false;
    while(chosen == false) //Randomly chooses which direction the ship will face (if possible) from the starting point
    {
        position = rand() % 4;
        switch(position)
        {
            case 0:
                if(board[lati-1][longi]==0 && lati-1 >=0)
                {
                    spaces.push_back(lati-1);
                    chosen = true;
                }
            break;
            case 1:
                if(board[lati+1][longi]==0 && lati+1 <= 9)
                {
                    spaces.push_back(lati+1);
                    chosen=true;
                }
            break;
            case 2:
                if(board[lati][longi-1]==0 && longi-1 >=0)
                {
                    spaces.push_back(longi-1);
                    chosen=true;
                }
            break;
            case 3:
                if(board[lati][longi+1]==0 && longi+1 <= 9)
                {
                    spaces.push_back(longi+1);
                    chosen=true;
                }
            break;
        }
    }

    if(position < 2) {	spaces.push_back(lati);}
    else {	spaces.push_back(longi);}

    vector<int> possibles; //Gathers all possible free spaces vertically if position is < 2 or horizontally if >=2
    if (position < 2)
    {
        for (int j=0;j<10;j++)
        {
            if(board[j][longi]==0){possibles.push_back(j);}
        }
    }else
    {
        for (int j=0;j<10;j++)
        {
            if(board[lati][j]==0){possibles.push_back(j);}
        }
    }

    for (int i=0;i<ship.length-2;i++) //For ships of length > 2 decides if and where the remainder of the ship will go
    {

        sort(spaces.begin(), spaces.end(), s_to_l);
        if(find(possibles.begin(), possibles.end(), spaces.at(0)-1) != possibles.end())
        {
            spaces.push_back(spaces.at(0)-1);
        }
        else if(find(possibles.begin(), possibles.end(), spaces.at(i+1)+1) != possibles.end())
        {
            spaces.push_back(spaces.at(i+1)+1);
        }
        else{return false;} //If there is not room to fit the ship in it's starting position returns false to try again
    }

    for(unsigned i=0; i<spaces.size(); i++) //Takes the decided coordinates for the ship and places them on the board
    {
        if(position < 2)
        {
            board[spaces.at(i)][longi] = ship.mark;
        }
        else
        {
            board[lati][spaces.at(i)] = ship.mark;
        }
    }
    return true; //Returns true to signal that the ship was successfully placed
}

void Computer::take_turn(Player *enemy)
{

    int x, y, lx = last_hit.x, ly = last_hit.y;

    if(on_hit){
        if(shots[lx - 1][ly] == 7 || shots[lx + 1][ly] == 7){

            for(int i=0;i<10;i++){
                if(shots[i+1][ly] == 7 && shots[i][ly] == 0){x=i;y=ly;break;}
                else if(shots[i+1][ly] == 0 && shots[i][ly] == 7){x=i+1;y=ly;break;}
            }
        }
        else if(shots[lx][ly - 1] == 7 || shots[lx][ly + 1] == 7){

            for(int i=0;i<10;i++){
                if(shots[lx][i+1] == 7 && shots[lx][i] == 0){x=lx;y=i;break;}
                else if(shots[lx][i+1] == 0 && shots[lx][i] == 7){x=lx;y=i+1;break;}
            }
        }
        else{
            bool chosen = false;
            while(chosen == false){
                int pos = rand() % 4;
                switch(pos){
                    case 0: if(shots[lx-1][ly]==0 && lx-1 >= 0){x=lx-1;y=ly;chosen = true;}
                    break;
                    case 1: if(shots[lx+1][ly]==0 && lx+1 <= 9){x=lx+1;y=ly;chosen = true;}
                    break;
                    case 2: if(shots[lx][ly-1]==0 && ly-1 >= 0){x=lx;y=ly-1;chosen = true;}
                    break;
                    case 3: if(shots[lx][ly+1]==0 && ly+1 <= 9){x=lx;y=ly+1;chosen = true;}
                    break;
                }
            }
        }
    }else{
        while(shots[x = rand() % 10][y = rand() % 10] > 5);
    }

    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem();

    qDebug() << x << y << shots[x][y];
    if(enemy->is_a_hit(x,y))
    {
        shots[x][y] = 7;
        on_hit = true;
        last_hit = Coordinate(x,y);
        if(enemy->get_sank().size() > has_sank){
            has_sank += 1;

            int s_ship = enemy->board[x][y];
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(enemy->board[i][j] == s_ship){
                        shots[i][j] = 8;
                    }
                }
            }
            on_hit = false;
        }
        qDebug() << QString("It was");
        pi->setPixmap(QPixmap(":/images/fire.png"));
        pi->setPos(400+y*35,425+x*35);
    }else
    {
        shots[x][y] = 6;
        qDebug() << QString("It wasnt");
        pi->setPixmap(QPixmap(":/images/splash.png"));
        pi->setPos(400+y*35,425+x*35);
    }

    pi->show();
    game->scene->addItem(pi);


    if(enemy->has_lost()){
        game->gameOver(enemy->get_name());
    }else{
        game->setWhoseTurn("player1");
    }
}
