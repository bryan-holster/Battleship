#include "Square.h"
#include <QPointF>
#include <QVector>
#include <QDebug>
#include "Game.h"

extern Game* game;

Square::Square(QGraphicsItem *parent){

    QRect sqPoints = QRect(QPoint(0,0),QPoint(35,35));

    QRectF square(sqPoints);

    setRect(square);

    isPlaced = false;
    isRadar = false;
}

bool Square::getIsPlaced()
{
    //qDebug() << QString("mousePressEvent") << isPlaced;
    return isPlaced;
}

bool Square::getIsRadar()
{
    return isRadar;
}

int Square::getXCoord()
{
    return x_coord;
}

int Square::getYCoord()
{
    return y_coord;
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(getIsRadar() == false){
        //game->placeShip(this);
        qDebug() << QString("mousePressEvent") << this->pos() << this->getXCoord() << this->getYCoord();
    }else{
        if(game->getWhoseTurn() == "player1" && game->getLocked()){
            //qDebug() << QString("radarPosition") << this->getXCoord() << this->getYCoord();
            game->player1->take_turn(game->computer,this->getXCoord(),this->getYCoord());
        }
    }
}

void Square::setIsPlaced(bool b)
{
    isPlaced = b;
}

void Square::setIsRadar(bool b)
{
    isRadar = b;
}

void Square::setCoords(int x, int y)
{
    x_coord = x;
    y_coord = y;
}
