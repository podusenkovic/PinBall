#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

class Helper;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(Helper *w, QWidget *parent);

signals:

public slots:
   void animate();

public:
   void paintEvent(QPaintEvent *event = nullptr);

private:
    Helper *helper;
    int elapsed;
};

#endif // WIDGET_H
