#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QTimer>
#include <QMouseEvent>
#include <QtNetwork>
#include <QDebug>
#include <QVector>

QSize winSize = QSize(1000,700);

QPoint startPoint;  
QPoint startSpeed;
bool mReleased = false;
bool PawsMoving = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    client = new Client;
    client->show();
    
    this->move(100,10);
    Widget *drawPlace = new Widget(&helper, this);
    setFixedSize(winSize);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(drawPlace, 0, 0);
    setLayout(layout);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), drawPlace, SLOT(animate()));
    timer->start(15);
   
    connect(client, SIGNAL(got_wall()), this, SLOT(initWalls()));        
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
    
    //QTimer::singleShot(100, client, SLOT(sendBall(Ball())));
    client->close();
    
    QVector<QString> w = client->throwWalls();
    helper.setWalls(w);
}
