#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helper.h"


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event = 0) override;
    void mouseReleaseEvent(QMouseEvent *event = 0) override;
private:
    Ui::MainWindow *ui;
    Helper helper;
};

#endif // MAINWINDOW_H
