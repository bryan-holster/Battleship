#include "Human.h"
#include "Game.h"
#include <QDebug>

extern Game* game;

void Human::setShips(QList<Ship *> ships)
{
    int x,y;

    for(int i = 0; i < ships.size(); i++){
        qDebug() << ships[i]->pos() << ships[i]->rect() << ships[i]->getLength();
        x = (ships[i]->pos().rx() - 400)/35;
        y = (ships[i]->pos().ry() - 425)/35;
        board[y][x] = i+1;
        for(int l=0;l<ships[i]->getLength()-1;l++){
            if(ships[i]->rect().height() > ships[i]->rect().width()){
                board[++y][x] = i+1;
            }else{
                board[y][++x] = i+1;
            }
        }
    }
}

void Human::take_turn(Player *enemy, int x, int y)
{
    if(shots[x][y] == 6 || shots[x][y] == 7){
        return;
    }else{
        QGraphicsPixmapItem* pi = new QGraphicsPixmapItem();

        if(enemy->is_a_hit(x,y)){
            pi->setPixmap(QPixmap(":/images/fire.png"));
            pi->setPos(400+y*35,25+x*35);
            shots[x][y] = 7;
        }else{
            pi->setPixmap(QPixmap(":/images/splash.png"));
            pi->setPos(400+y*35,25+x*35);
            shots[x][y] = 6;
        }

        pi->show();
        game->scene->addItem(pi);

        if(enemy->has_lost()){
            game->gameOver(enemy->get_name());
        }else{
            game->setWhoseTurn("computer");
            game->takeTurn();
        }
    }
}

