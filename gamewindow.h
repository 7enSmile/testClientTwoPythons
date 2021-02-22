#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "QWidget"
#include <QPainter>
#include <QPushButton>
#include <QLabel>
class GameWindow:public QWidget
{
public:
    GameWindow();
private:
    static const int DOT_WIDTH=40;
    static const int DOT_HIGHT=40;
    static const int FILD_WIDTH=15;
    static const int FILD_HIGHT=15;
    void drowWindow();
    void paintEvent(QPaintEvent *event);
    void drowArea();
    void drowElements();
    QPushButton *buttExit;
    QLabel *score;
    QLabel *timer;
};

#endif // GAMEWINDOW_H
