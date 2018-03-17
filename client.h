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

#include "ball.h"

class Client : public QDialog
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    
    QVector<QString> throwWalls();
    void sendBall(Ball);
signals:
    void got_ball();
    void got_wall();
    
private slots:
    void requestWalls();
    void readData();
    void displayError(QAbstractSocket::SocketError);
    void enableGetWallsButton();
    void sessionOpened();
    void transWall();
    void transBall();
    
private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *getWallsButton = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    
    QDataStream in;
    QDataStream out;
    
    QString currentData;
    
    QVector<QString> allWalls;
    
    QNetworkSession *networkSession = nullptr;
    
};

#endif // CLIENT_H  
