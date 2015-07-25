#include "Ship.h"
#include <QDebug>
#include "Game.h"

extern Game* game;

Ship::Ship(QString n, int l, QGraphicsItem *parent)
{
    name = n;
    length = l;

    QRect sqPoints = QRect(QPoint(0,0),QPoint(35,35*l));
    QRectF square(sqPoints);
    setRect(square);

    isPlaced = false;
    isPickedUp = false;
}

QList<Square *> Ship::getSpaces()
{
    return spaces;
}

QString Ship::getName()
{
    return name;
}

int Ship::getLength()
{
    return length;
}

bool Ship::getIsPlaced()
{
    return isPlaced;
}

bool Ship::getIsPickedUp()
{
    return isPickedUp;
}

void Ship::setIsPlaced(bool b)
{
    isPlaced = b;
}

void Ship::setIsPickedUp(bool b)
{
    isPickedUp = b;
}

void Ship::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!game->getLocked()){
        if(getIsPickedUp() == false){
            game->pickUpShip(this);
            this->setIsPickedUp(true);
            this->setIsPlaced(false);
        }else{
            int tx = (int)(this->pos().rx()- 400)/35;
            int ty = (int)(this->pos().ry()-425)/35;

            if(tx >= 0 && tx <= 9 && ty >= 0 && ty <= 9){
                int oy = this->rect().height();
                int ox = this->rect().width();
                if((ox < oy && this->getLength()+ty <= 10) || (ox > oy && this->getLength()+tx <= 10)){
                    game->placeShip(tx,ty);
                }
            }

            qDebug() << QString("mousePressEvent") << tx << ty;
        }
    }
}
