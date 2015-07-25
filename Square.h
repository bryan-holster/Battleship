#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Square: public QGraphicsRectItem{
public:
    // constructors
    Square(QGraphicsItem* parent=NULL);
    bool getIsPlaced();
    bool getIsRadar();
    int getXCoord();
    int getYCoord();

    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void setIsPlaced(bool b);
    void setIsRadar(bool b);
    void setCoords(int x, int y);

private:
    bool isPlaced;
    bool isRadar;
    int x_coord;
    int y_coord;

};

#endif // SQUARE_H
