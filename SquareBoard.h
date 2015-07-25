#ifndef SQUAREBOARD_H
#define SQUAREBOARD_H

#include <QList>
#include "Square.h"

class SquareBoard
{
public:
    SquareBoard();

    QList<Square*> getSquares();
    void placeSquares(int,int,int,int,bool);

private:
    QList<Square*> squares;
    void createSquareColumn(int,int,int,bool,int);
};

#endif // SQUAREBOARD_H
