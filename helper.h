#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "ball.h"
#include "wall.h"

class Helper : public QObject
{
    Q_OBJECT
public:
    Helper();
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void setWalls(QVector<QString> wall);
    Ball *getBall(){
        return ball;
    }
    void addExternBall(QString b);
    
private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    Ball *ball = nullptr;
    QVector<Ball*> externBalls;
    QVector<int> ballsIDs;
    QVector<QColor> ballsColors;
    Wall *wall = nullptr;
    Wall *paws;
    int numWall;
    
signals:
    void createdBall();
    
};

#endif
