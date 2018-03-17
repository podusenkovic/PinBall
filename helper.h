#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "ball.h"
#include "wall.h"

class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void setWalls(QVector<QString> wall);
private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    Ball *ball = nullptr;
    Wall *wall = nullptr;
    Wall *paws;
    int numWall;
};

#endif
