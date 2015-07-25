#ifndef SHIP_H
#define SHIP_H

#include <QList>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "Square.h"

class Ship: public QGraphicsRectItem
{
public:
    Ship(QString n, int l,QGraphicsItem* parent=NULL);

    QList<Square*> getSpaces();
    QString getName();
    int getLength();
    bool getIsPlaced();
    bool getIsPickedUp();
    void setIsPlaced(bool b);
    void setIsPickedUp(bool b);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QString name;
    int length;
    bool isPlaced;
    bool isPickedUp;
    QList<Square*> spaces;
};

#endif // SHIP_H
