#ifndef BALL_H
#define BALL_H

#define PI 3.1415

#include <QPoint>
#include <QRect>
#include <QLine>


static double max(double a, double b){
    if (a > b) 
        return a;
    else return b;
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
    friend double max(double a, double b);
    friend double min(double a, double b);
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
    
    void updateSpeed(){
        speed += accel;
    }
    
    void updateCoord(){
        this->checkBounds();
        coord += speed;
        //coord = QPoint((coord.x() + speed.x()),
        //               (coord.y() + speed.y()));
    }
    
    void checkBounds(){
        if (coord.x() + radius > winSize.width() || coord.x() - radius < 0){
            speed.setX(speed.x()*(-1));
            accel.setX(accel.x()*(-1));
            return;
        }
        if (coord.y() + radius > winSize.height() || coord.y() - radius < 0){
            speed.setY(speed.y()*(-1));
            accel.setY(accel.y()*(-1));
            return;
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
            if(    (coord.x() > min(line.x1(),line.x2()) - radius)
                && (coord.x() < max(line.x1(),line.x2()) + radius)
                && (coord.y() > min(line.y1(),line.y2()) - radius)
                && (coord.y() < max(line.y1(),line.y2()) + radius)){
            
            QPoint norma = QPoint(y1 - y2, x2 - x1);
            double NormAndSpeed = (speed.x()*norma.x() + speed.y()*norma.y());
            QPoint newSpeed = speed - 2 * norma * (NormAndSpeed/(Abs(norma)*Abs(norma)));
            
            speed = newSpeed;
            
        }
            
            
    }
    
    
};

#endif // BALL_H
