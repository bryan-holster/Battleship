#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "SquareBoard.h"
#include "Ship.h"
#include "Button.h"
#include "Human.h"
#include "Computer.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
    void pickUpShip(Ship* ship);
    void placeShip(int, int);
    void removeFromDeck(Ship* ship);
    void takeTurn();
    void gameOver(QString);
    void setWhoseTurn(QString);
    QString getWhoseTurn();
    bool getLocked();

    //events
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);

    // public attributes
    QGraphicsScene* scene;
    SquareBoard* squareBoard1;
    SquareBoard* squareBoard2;
    Ship* shipToPlace;
    QPointF originalPos;
    Human* player1;
    Computer* computer;

public slots:
    void start();
    void restart();
    void lockShips();

private:
    void drawPanel(int x,int y,int width,int height,QColor color,double opacity);
    void drawGUI();
    void createNewShips();
    void createFirstShips();
    void drawShips();

    QString whoseTurn = "player1";
    QList<Ship* > playerShips;
    bool locked;
    Button* setButton;
    QGraphicsTextItem* helpText;

};

#endif // GAME_H
