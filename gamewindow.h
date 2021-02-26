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
#include <QColor>
#include "python.h"
class GameWindow:public QWidget
{
     Q_OBJECT

public:
    GameWindow();
    void keyPressEvent(QKeyEvent *)override;
public slots:
    void sockConnect();
private:
    static const int DOT_WIDTH=40;
    static const int DOT_HIGHT=40;
    static const int FILD_WIDTH=20;
    static const int FILD_HIGHT=20;
    void drowWindow();
    void paintEvent(QPaintEvent *event)override;
    void drowArea();
    void drowElements();
    void drowPythons();
    QPushButton *buttExit;
    QLabel *score;
    QLabel *timer;
    QTcpSocket *socket;
    QString data;
    QJsonDocument doc;
    QJsonParseError docERR;
    QVector<QPoint>fruits;
    QVector<Python*>pythons;
    void drowFruits();


};

#endif // GAMEWINDOW_H
