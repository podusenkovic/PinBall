#include "mainwindow.h"

#include <QGridLayout>
#include <QTimer>
#include <QMouseEvent>
#include <QtNetwork>
#include <QDebug>
#include <QVector>

QSize winSize = QSize(500, 500);

QPoint startPoint;  
QPoint startSpeed;
bool mReleased = false;
bool PawsMoving = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{    
    this->move(100,10);
    Widget *drawPlace = new Widget(&helper, this);
    setFixedSize(winSize);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(drawPlace, 0, 0);
    setLayout(layout);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), drawPlace, SLOT(animate()));
    timer->start(15);
 
    client = new Client;
    client->show();
    client->move(100, 550);
    
    connect(client, SIGNAL(got_wall()), this, SLOT(initWalls()));        
    connect(client, SIGNAL(got_ball()), this, SLOT(addBallToPlace()));
}

MainWindow::~MainWindow()
{
    
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    startPoint = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    mReleased = true;
    startSpeed = (startPoint - event->pos())/10;
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Space)
        PawsMoving = true;
}

void MainWindow::initWalls(){
    QVector<QString> w = client->throwWalls();
    helper.setWalls(w);
    connect(&helper, SIGNAL(createdBall()), this, SLOT(sendingBall()));
}


void MainWindow::sendingBall(){
    client->setBall(*helper.getBall());
    QTimer::singleShot(3, client, SLOT(sendBall()));
}

void MainWindow::addBallToPlace(){
    QString b = client->getNewBall();
    qDebug() << "adding ball to play" << b;
    helper.addExternBall(b);
}
