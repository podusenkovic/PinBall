#ifndef WALL_H
#define WALL_H

#include <QPoint>
#include <QRect>
#include <QLine>

class Wall
{
    QPoint p1,p2;
    QPoint center;
public:
    Wall(QPoint p1 = QPoint(0,0), QPoint p2 = QPoint(0,0)){
        this->p1 = p1;
        this->p2 = p2;
        center = (p1 + p2) / 2;
    }
    
    QPoint *getEndPoints(){
        QPoint *pnts = new QPoint[2];
        pnts[0] = p1;
        pnts[1] = p2;
        return pnts;
    }
    
    double getLen(){
        double w = abs(p1.x() - p2.x());
        double h = abs(p1.y() - p2.y());
        return sqrt(w*w + h*h);
    }
    
    QPoint getCenter(){
        return center;
    }
    
    QLine line(){
        return QLine(p1,p2);
    }
    
};

#endif // WALL_H
