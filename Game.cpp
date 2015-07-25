#include "Game.h"
#include "SquareBoard.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <QGraphicsTextItem>
#include <QDebug>

Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,800);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,800);
    QImage bg(":/images/mm_background.jpg");
    QBrush brush(bg);
    scene->setBackgroundBrush(bg);
    setScene(scene);

    shipToPlace = NULL;
    locked = false;
}

void Game::displayMainMenu()
{
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Battleship"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button* playButton = new Button(QString("Play"),200,50,15);
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"),200,50,15);
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::pickUpShip(Ship *ship)
{
    if(shipToPlace == NULL){
        qDebug() << QString("Picked up a ship");
        shipToPlace = ship;
        originalPos = ship->pos();
        return;
    }
}

void Game::placeShip(int tx, int ty)
{
    qDebug() << QString("Thinks ship is placed");
    if(shipToPlace){
        shipToPlace->setPos(QPointF(400+35*tx,425+35*ty));
        shipToPlace->setIsPlaced(true);
        shipToPlace->setIsPickedUp(false);
        shipToPlace = NULL;
    }
}

void Game::takeTurn()
{
    if(whoseTurn != "player1"){
        computer->take_turn(player1);
    }
}

void Game::gameOver(QString loser)
{
    for(int i = 0; i < scene->items().size();i++){
        scene->items()[i]->setEnabled(false);
    }

    drawPanel(0,0,800,800,Qt::black,0.65);
    drawPanel(200,200,400,400,Qt::lightGray,0.75);

    QGraphicsTextItem* overText = new QGraphicsTextItem(loser + " has lost");
    QFont overFont("comic sans", 25);
    overText->setFont(overFont);
    int txPos = this->width()/2 - overText->boundingRect().width()/2;
    int tyPos = 290;
    overText->setPos(txPos, tyPos);
    scene->addItem(overText);

    Button* playAgain = new Button(QString("Play Again"),200,50,15);
    int bxPos = this->width()/2 - playAgain->boundingRect().width()/2;
    int byPos = 365;
    playAgain->setPos(bxPos,byPos);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restart()));
    scene->addItem(playAgain);

    Button* quitButton = new Button(QString("Quit"),200,50,15);
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 440;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::setWhoseTurn(QString wT)
{
    whoseTurn = wT;
}

QString Game::getWhoseTurn()
{
    return whoseTurn;
}

bool Game::getLocked()
{
    return locked;
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(shipToPlace){
        shipToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::RightButton){
        if (shipToPlace){
            shipToPlace->setPos(originalPos);
            shipToPlace->setIsPickedUp(false);
            shipToPlace = NULL;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && shipToPlace){
        int h = shipToPlace->rect().height()-1;
        int w = shipToPlace->rect().width()-1;
        QPointF curr = shipToPlace->pos();
        scene->removeItem(shipToPlace);
        QRect sqPoints = QRect(QPoint(0,0),QPoint(h,w));
        QRectF square(sqPoints);
        shipToPlace->setRect(square);
        shipToPlace->setPos(curr);
        scene->addItem(shipToPlace);
    }
}

void Game::start(){

    scene->clear();

    shipToPlace = NULL;
    locked = false;
    whoseTurn = "player1";

    // test code TODO remove
    squareBoard1 = new SquareBoard();
    squareBoard2 = new SquareBoard();
    squareBoard1->placeSquares(400,25,10,10,true);
    squareBoard2->placeSquares(400,425,10,10,false);
    drawGUI();
    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem();
    pi->setPixmap(QPixmap(":/images/radar.jpg"));
    pi->setPos(401,26);
    pi->setOpacity(.6);
    pi->show();
    scene->addItem(pi);
    qDebug() << pi->pos();
    createNewShips();

    srand(time(NULL));
    player1 = new Human();
    computer = new Computer();
    player1->set_name("Player 1");
    computer->set_name("Computer");
}

void Game::restart()
{
    playerShips.clear();
    squareBoard1->getSquares().clear();
    squareBoard2->getSquares().clear();
    delete squareBoard1;
    delete squareBoard2;
    delete player1;
    delete computer;
    start();
}

void Game::lockShips()
{
    bool allPlaced = true;
    for(int i = 0; i < playerShips.size(); i++){
        if(!playerShips[i]->getIsPlaced()){allPlaced = false;break;}
    }
    if(allPlaced){
        locked = true;
        scene->removeItem(setButton);
        scene->removeItem(helpText);
        player1->setShips(playerShips);
        player1->debugBoard();
    }
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI()
{
    drawPanel(50,425,300,350,Qt::darkCyan,.4);

    QGraphicsTextItem* p1 = new QGraphicsTextItem("Player 1's ships");
    QFont playerFont("comic sans", 15);
    p1->setFont(playerFont);
    p1->setPos(125,425);
    scene->addItem(p1);

    setButton = new Button(QString("Done Setting Ships"),110,25,9);
    int bxPos = 145;
    int byPos = 725;
    setButton->setPos(bxPos,byPos);
    connect(setButton,SIGNAL(clicked()),this,SLOT(lockShips()));
    scene->addItem(setButton);

    helpText = new QGraphicsTextItem(QString("Press the 'R' key to rotate a ship"));
    QFont helpFont("comic sans", 12);
    helpText->setFont(helpFont);
    int txPos = 200 - helpText->boundingRect().width()/2;
    int tyPos = 695;
    helpText->setPos(txPos, tyPos);
    scene->addItem(helpText);
}

void Game::createNewShips()
{
    Ship* ca = new Ship("Carrier", 5);
    playerShips.append(ca);
    Ship* ba = new Ship("Battleship", 4);
    playerShips.append(ba);
    Ship* cr = new Ship("Cruiser", 3);
    playerShips.append(cr);
    Ship* su = new Ship("Submarine", 3);
    playerShips.append(su);
    Ship* de = new Ship("Destroyer", 2);
    playerShips.append(de);

    drawShips();
}


void Game::drawShips()
{/*
    for(int i = 0; i < player1Ships.size(); i++){
        scene->removeItem(player1Ships[i]);
    }*/

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);

    for(int i = 0; i < playerShips.size(); i++){
        Ship* ship = playerShips[i];
        ship->setPos(75+53.75*i,500);
        ship->setBrush(brush);
        scene->addItem(ship);
    }
}
