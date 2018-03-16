#ifndef BALL_H
#define BALL_H

#define PI 3.1415

#include <QPoint>
#include <QRect>
#include <QLine>
#include <QDebug>


static double max(double a, double b){
    if (a > b) 
        return a;
    else return b;
}

static double len(QPoint a, QPoint b){
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + \
                (a.y() - b.y()) * (a.y() - b.y()));
}

static double min(double a, double b){
    if (a < b) 
        return a;
    else return b;
}

static double Abs(QPoint a){
    return sqrt(a.x()*a.x() + a.y()*a.y());
}

extern QSize winSize;

class Ball
{
    QPoint coord;
    double radius;
    QPoint speed;
    QPoint accel;
public:
    Ball(){
       coord = QPoint(0,0);
       radius = 1;
       speed = QPoint(0,0);
       accel = QPoint(0,0);
    }

    Ball(QPoint c, double r, QPoint s, QPoint a){
       coord = c;
       radius = r;
       speed = s;
       accel = a;
    }    
    
    QPoint GetCoord(){
        return coord;
    }
    double getRadius(){
        return radius;
    }
    QPoint getSpeed(){
        return speed;
    }
    QPoint getAccel(){
        return accel;   
    }
    
    QRect rect(){
        return QRect(coord + QPoint(-radius, -radius), 
                     coord + QPoint(radius, radius));
    }
    
    void setCoord(QPoint p){
        coord = p;
    }
    void setRadius(double r){
        radius = r;
    }
    void setSpeed(QPoint sp){
        speed = sp;
    }
    void setAccel(QPoint ac){
        accel = ac;
    }
    
    void updateAccel(){
        if(abs(speed.y()) <= 3 && coord.y() + radius >= winSize.height()){
            accel.setY(0);
            speed.setY(0);
        }
    }
    
    void updateSpeed(){
        if (speed.y() == 0 && coord.y() + radius >= winSize.height()){
            accel.setX(-speed.x()/5);
        }
        if(abs(speed.y()) <= 9 && coord.y() + radius >= winSize.height()){
            qDebug() << speed.y();   
            speed.setY(0);
        }
        speed += accel;
    }
    
    void updateCoord(){
        this->checkBounds();
        coord += speed;
        //coord = QPoint((coord.x() + speed.x()),
        //               (coord.y() + speed.y()));
    }
    
    void checkBounds(){
        if (coord.x() + radius >= winSize.width() || coord.x() - radius <= 0){
            coord.setX((coord.x() + radius >= winSize.width()) ? coord.x() - speed.x() : coord.x() - speed.x());
            speed.setX(speed.x()*(-0.9));
            accel.setX(accel.x()*(-0.9));
            //return;
        }
        if (coord.y() + radius >= winSize.height() || coord.y() - radius <= 0){
            coord.setY((coord.y() + radius >= winSize.height()) ? coord.y() - speed.y() : coord.y() - speed.y());            
            speed.setY(speed.y()*(-0.8));
            //accel.setY(accel.y()*(-1));
            //return;
        }
    }
    
    void checkBounds(QLine line){
        double x0 = coord.x(),
               y0 = coord.y(),
               x1 = line.x1(),  
               y1 = line.y1(),
               x2 = line.x2(),
               y2 = line.y2();
        
       
        double d = abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1)
                / sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1));
        
        if ((d < radius))
            /*if(len(line.p1(), coord) < radius || len(line.p2(), coord) < radius){
                QPoint newSpeed = QPoint(-speed.x(), -speed.y());
                speed = newSpeed;
                return;
            }*/
                
            if(    (coord.x() > min(x1,x2) - radius)
                && (coord.x() < max(x1,x2) + radius)
                && (coord.y() > min(y1,y2) - radius)
                && (coord.y() < max(y1,y2) + radius)){
            
            QPoint norma = QPoint(y1 - y2, x2 - x1);
            double NormAndSpeed = (speed.x()*norma.x() + speed.y()*norma.y());
            QPoint newSpeed = speed - 2 * norma * (NormAndSpeed/(Abs(norma)*Abs(norma)));
            if (d < radius / 2)
                speed = -speed;
            else speed = newSpeed * 0.9;
            coord += speed;
            
        }
    }
};

#endif // BALL_H
