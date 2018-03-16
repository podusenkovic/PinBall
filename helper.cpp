#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <time.h>

#define numWall 3

extern QPoint startPoint;
extern QPoint startSpeed;
extern bool mReleased;
extern QSize winSize;
extern bool PawsMoving;

bool needDraw = false;

Helper::Helper()
{
    srand(time(NULL));

    background = QBrush(QColor(253, 83, 52));
    circleBrush = QBrush(QColor(49, 110, 115));
    circlePen = QPen(Qt::yellow, 3);
    circlePen.setWidth(3);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    
    wall = new Wall[numWall];
    for(int i = 0; i < numWall; i++)
        wall[i] = Wall(QPoint(rand() % (winSize.width() - 100) + 50,
                              rand() % (winSize.height() - 100) + 50),
                       QPoint(rand() % (winSize.width() - 100) + 50,
                              rand() % (winSize.height() - 100) + 50));
    
    paws = new Wall[2];
    paws[0] = Wall(QPoint(50,  winSize.height() - 50), 
                   QPoint(200, winSize.height() - 50));
    paws[1] = Wall(QPoint(250, winSize.height() - 50), 
                   QPoint(400, winSize.height() - 50));
    
}


void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);

    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(QPen(Qt::black,1));
    painter->setFont(textFont);
    
    if(mReleased){
        mReleased = false;
        needDraw = true;                
        ball = new Ball(startPoint, 20, startSpeed, QPoint(0,1));
    }
    if(needDraw){      
        ball->updateAccel();
        ball->updateCoord();
        ball->updateSpeed();
        for(int i = 0; i < numWall; i++)
            ball->checkBounds(wall[i].line());
        for(int i = 0; i < 2; i++)
            ball->checkBounds(paws[i].line());
        painter->drawEllipse(ball->rect());
    }
    painter->setPen(QPen(QColor(59, 66, 76),4));
    for(int i = 0; i < numWall; i++)
        painter->drawLine(wall[i].line());
    
    for(int i = 0; i < 2; i++)
        painter->drawLine(paws[i].line());
    
    if(PawsMoving){
        //bool a = paws[0].moveLines('l');
        //bool b = paws[1].moveLines('r');
        if(!moveblyat(&paws[0], &paws[1]))
            PawsMoving = false;       
    }
    
    painter->restore();

    painter->setPen(textPen);
    painter->setFont(textFont);
}
