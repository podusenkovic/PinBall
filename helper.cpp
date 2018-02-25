#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

extern QSize winSize;

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
    
    
    ball = new Ball(QPoint(100,50), 20, QPoint(6,10), QPoint(0,0));
    wall = new Wall(QPoint(100,300), QPoint(430,450));
}


void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    //painter->translate(100, 100);

    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(QPen(Qt::black,1));
    //painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    ball->updateCoord();
    ball->updateSpeed();
    ball->checkBounds(wall->line());
    painter->drawEllipse(ball->rect());
    
    painter->setPen(QPen(Qt::yellow,3));
    painter->drawLine(wall->line());
    
    painter->restore();

    painter->setPen(textPen);
    painter->setFont(textFont);
    //painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
}
