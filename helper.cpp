#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

extern QPoint startPoint;
extern QPoint startSpeed;
extern bool mReleased;
extern QSize winSize;

bool needDraw = false;

Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::yellow, 3);
    circlePen.setWidth(3);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    
    wall = new Wall(QPoint(150,150), QPoint(500,390));        
    
}


void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);

    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(QPen(Qt::black,1));

    
    if(mReleased){
        mReleased = false;
        needDraw = true;                
        ball = new Ball(startPoint, 20, startSpeed, QPoint(0,0));
    }
    if(needDraw){
        ball->updateCoord();
        ball->updateSpeed();
        ball->checkBounds(wall->line());
        painter->drawEllipse(ball->rect());
    }
    painter->setPen(QPen(Qt::yellow,3));
    painter->drawLine(wall->line());
    
    painter->restore();

    painter->setPen(textPen);
    painter->setFont(textFont);
}
