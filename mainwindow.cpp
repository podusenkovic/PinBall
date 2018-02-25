#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widget.h"

#include <QGridLayout>
#include <QTimer>

QSize winSize = QSize(700,700);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //this->setWindowTitle(QString("PinBall, WHOHOO"));
    Widget *drawPlace = new Widget(&helper, this);
    setFixedSize(winSize);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(drawPlace, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), drawPlace, SLOT(animate()));
    timer->start(10);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
