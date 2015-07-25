#include "SquareBoard.h"
#include "Game.h"

extern Game* game;

SquareBoard::SquareBoard()
{

}

QList<Square *> SquareBoard::getSquares()
{
    return squares;
}

void SquareBoard::placeSquares(int x,int y,int cols,int rows, bool r)
{
    int X_SHIFT = 35;

    for (int i = 0, n = cols; i < n; i++){
        createSquareColumn(x+X_SHIFT*i,y,rows,r,i);
    }
}

void SquareBoard::createSquareColumn(int x, int y, int numofRows,bool r,int curr_i)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    for(int i = 0; i < numofRows; i++)
    {
        Square* square = new Square();
        square->setPos(x,y+35*i);

        square->setIsPlaced(true);
        if(r){
            square->setIsRadar(true);
        }else{
            square->setBrush(brush);
            square->setOpacity(.6);
        }

        square->setCoords(i,curr_i);
        squares.append(square);
        game->scene->addItem(square);
    }
}

