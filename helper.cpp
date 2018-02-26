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

bool needDraw = false;

Helper::Helper()
{
    srand(time(NULL));
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
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
        ball = new Ball(startPoint, 20, startSpeed, QPoint(0,0));
    }
    if(needDraw){
        
        painter->drawText(event->rect(),
                          QString::number(ball->getSpeed().x()));        
        
        ball->updateCoord();
        ball->updateSpeed();
        for(int i = 0; i < numWall; i++)
            ball->checkBounds(wall[i].line());
        
        painter->drawEllipse(ball->rect());
    }
    painter->setPen(QPen(Qt::yellow,3));
    for(int i = 0; i < numWall; i++)
        painter->drawLine(wall[i].line());
    
    painter->restore();

    painter->setPen(textPen);
    painter->setFont(textFont);
}
