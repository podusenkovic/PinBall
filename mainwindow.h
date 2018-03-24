#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helper.h"
#include "widget.h"
#include "client.h"

#include <QMainWindow>

/*namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void initWalls();
    void sendingBall();
    void addBallToPlace();
    void movePaws();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event = 0) override;
    void mouseReleaseEvent(QMouseEvent *event = 0) override;
    void keyPressEvent(QKeyEvent *event) override;    
private:
    //Ui::MainWindow *ui;
    Helper helper;
    Client *client;
};

#endif // MAINWINDOW_H
