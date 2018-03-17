#include "helper.h"
#include "widget.h"

#include <QPainter>
#include <QTimer>
#include <QtGui>
#include <QtCore>

extern QSize winSize;

Widget::Widget(Helper* _helper, QWidget *parent) :
    QWidget(parent),
    helper(_helper)
{
    elapsed = 0;
    setFixedSize(winSize);
}

void Widget::animate(){
    elapsed =(elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    this->update();
}


void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
}

