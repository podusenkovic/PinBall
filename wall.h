#ifndef WALL_H
#define WALL_H

#define PI 3.1415

#include <QPoint>
#include <QRect>
#include <QLine>
#include <QTimer>

#include <math.h>

class Wall
{
    QPoint p1,p2;
    QPoint center;
public:
    friend bool moveblyat(Wall *a, Wall *b){
        static int delta = 0;
        static int sum = 0;
    
        static bool up = true;
       
        if (sum <= -52)
            up = !up;
        
        if (up)
            delta = -2;
        else
            delta = 2;
        
        sum += delta;
        a->p2 = QPoint(a->p2.x(), 
                       a->p2.y() + delta);
        b->p1 = QPoint(b->p1.x(), 
                       b->p1.y() + delta);
        
            if (sum >= 0){
            delta = 0;
            sum = 0;
            up = true;
            return false;
    }
    return true;    
}
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
    
    void setP1(QPoint p1){
        this->p1 = p1;
    }

    void setP2(QPoint p2){
        this->p2 = p2;
    }
    
        
    bool moveLines(char c){
   
        static int delta = 0;
        static int sum = 0;
        
        
        static bool up = true;
       
        if (sum <= -128)
            up = !up;
        
        if (up)
            delta = -2;
        else
            delta = 2;
        
        if (c == 'l'){
            sum += delta;
            p2 = QPoint(p2.x(), 
                        p2.y() + delta);
        }
        else if (c == 'r'){
            sum += delta;
            p1 = QPoint(p1.x(), 
                        p1.y() + delta);
        }
        
        if (sum > 0){
            delta = 0;
            sum = 0;
            up = true;
            return false;
        }
        return true;
    }
};



#endif // WALL_H
