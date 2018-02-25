#include "helper.h"
#include "widget.h"

#include <QPainter>
#include <QTimer>

extern QSize winSize;

Widget::Widget(Helper *helper, QWidget *parent) :
    QWidget(parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(winSize);
}

void Widget::animate(){
    elapsed =(elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    this->update();
}


void Widget::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}
