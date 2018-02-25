#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widget.h"

#include <QGridLayout>
#include <QTimer>
#include <QMouseEvent>

QSize winSize = QSize(1000,700);

QPoint startPoint;
QPoint startSpeed;
bool mReleased = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->move(100,10);
    Widget *drawPlace = new Widget(&helper, this);
    setFixedSize(winSize);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(drawPlace, 0, 0);
    setLayout(layout);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), drawPlace, SLOT(animate()));
    timer->start(5);    
    ui->setupUi(this);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    startPoint = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    mReleased = true;
    startSpeed = (startPoint - event->pos())/10;
}
