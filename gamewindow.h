#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "QWidget"
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include<QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QtGui>
class GameWindow:public QWidget
{
     Q_OBJECT

public:
    GameWindow();
    void keyPressEvent(QKeyEvent *event)override;
public slots:
    void sockConnect();
private:
    static const int DOT_WIDTH=40;
    static const int DOT_HIGHT=40;
    static const int FILD_WIDTH=15;
    static const int FILD_HIGHT=15;
    void drowWindow();
    void paintEvent(QPaintEvent *event)override;
    void drowArea();
    void drowElements();
    void drowPython();
    QPushButton *buttExit;
    QLabel *score;
    QLabel *timer;
    QTcpSocket *socket;
    QString data;
    QJsonDocument doc;
    QJsonParseError docERR;
    QVector<QPoint>dots;


};

#endif // GAMEWINDOW_H
