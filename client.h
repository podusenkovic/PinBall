#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QDialog>
#include <QTcpSocket>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDataStream>
#include <QNetworkSession>
#include <QHostInfo>
#include <QDialogButtonBox>
#include <QNetworkConfigurationManager>
#include <QVector>
#include <QTcpServer>

#include "ball.h"

class Client : public QDialog
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    
    void setBall(Ball b){
        this->b = b;
    }
    
    QVector<QString> throwWalls();
    
    QString getNewBall(){
        return newBall;
    }
signals:
    void got_ball();
    void got_wall();
    
public slots:
    void sendBall();
    
private slots:
    void requestWalls();
    void readData();
    void displayError(QAbstractSocket::SocketError);
    void enableGetWallsButton();
    void sessionOpened();
    void transWall();
    void transBall();
    void readBall();
    void finalReadBall();
    //void sendIP();
private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *getWallsButton = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QTcpServer *tcpServer = nullptr;
    
    QDataStream in;
    //QDataStream out;
    
    QString currentData;
    
    Ball b;
    QVector<QString> allWalls;
    QString newBall;
    
    QNetworkSession *networkSession = nullptr;
    
    int id;
    
};

#endif // CLIENT_H  
