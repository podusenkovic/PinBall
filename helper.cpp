#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <time.h>
#include <QDebug>


extern QPoint startPoint;
extern QPoint startSpeed;
extern bool mReleased;
extern QSize winSize;
extern bool PawsMoving;

bool needDraw = false;

Helper::Helper():
    QObject(nullptr)
{
    srand(time(NULL));

    background = QBrush(QColor(253, 83, 52));
    circleBrush = QBrush(QColor(49, 110, 115));
    circlePen = QPen(Qt::yellow, 3);
    circlePen.setWidth(3);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    
      
   /*wall[i] = Wall(QPoint(rand() % (winSize.width() - 100) + 50,
                           rand() % (winSize.height() - 100) + 50),
                    QPoint(rand() % (winSize.width() - 100) + 50,
                           rand() % (winSize.height() - 100) + 50));*/

    paws = new Wall[2];
    paws[0] = Wall(QPoint(50,  winSize.height() - 50), 
                   QPoint(200, winSize.height() - 50));
    paws[1] = Wall(QPoint(250, winSize.height() - 50), 
                   QPoint(400, winSize.height() - 50));
    
}


void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(QRect(QPoint(), winSize), background);

    painter->save();
    painter->setPen(QPen(Qt::black,1));
    painter->setFont(textFont);
    
    if(mReleased){
        mReleased = false;
        needDraw = true;                
        ball = new Ball(startPoint, 20, startSpeed, QPoint(0,1));
        emit createdBall();
    }
    if(needDraw){
        for (int i = 0; i < externBalls.size(); i++)
        {
            painter->setBrush(QBrush(QColor(0, 0, 0)));
            externBalls[i]->updateAccel();
            externBalls[i]->updateCoord();
            externBalls[i]->updateSpeed();
            if(wall != nullptr){
                for(int j = 0; j < numWall; j++)
                    externBalls[i]->checkBounds(wall[j].line());
            }
            for(int j = 0; j < 2; j++)
                externBalls[i]->checkBounds(paws[j].line());
            painter->drawEllipse(externBalls[i]->rect());
        }
        painter->setBrush(circleBrush);
        ball->updateAccel();
        ball->updateCoord();
        ball->updateSpeed();
        if(wall != nullptr){
            for(int i = 0; i < numWall; i++)
                ball->checkBounds(wall[i].line());
        }
        for(int i = 0; i < 2; i++)
            ball->checkBounds(paws[i].line());
        painter->drawEllipse(ball->rect());
    }
    painter->setPen(QPen(QColor(59, 66, 76),4));
    if(wall != nullptr){
        for(int i = 0; i < numWall; i++)
            painter->drawLine(wall[i].line());
    }
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

void Helper::setWalls(QVector<QString> walls){
    numWall = walls.size();
    wall = new Wall[numWall];
    for(int i = 0; i < numWall; i++){
        QStringList wallCoord = walls[i].split(QChar('.'));
        wall[i] = Wall(QPoint(wallCoord[0].toInt(),
                              wallCoord[1].toInt()),
                       QPoint(wallCoord[2].toInt(),
                              wallCoord[3].toInt()));
    }
}

void Helper::addExternBall(QString b){
    QStringList list = b.split(":");
    Ball *ball = new Ball(QPoint(list[0].toInt(), list[1].toInt()),
                          list[2].toInt(),
                          QPoint(list[3].toInt(), list[4].toInt()),
                          QPoint(list[5].toInt(), list[6].toInt()));
    externBalls.push_back(ball);
}























