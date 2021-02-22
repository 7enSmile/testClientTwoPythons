#include "gamewindow.h"

GameWindow::GameWindow()
{
    resize(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH,DOT_HIGHT*FILD_HIGHT);
    this->setWindowTitle("TwoPythons");
    drowElements();

    repaint();
}
void GameWindow::paintEvent(QPaintEvent *event){
    drowWindow();
}

void GameWindow::drowArea()
{
    QPainter painter(this);
    painter.setBrush((QBrush(Qt::black, Qt::SolidPattern)));
    for(int i=1;i*DOT_WIDTH<=DOT_WIDTH*FILD_WIDTH;i++){
      painter.drawLine(i*DOT_WIDTH,0,i*DOT_WIDTH,FILD_HIGHT*DOT_HIGHT);
    }
    for(int i=1;i*DOT_HIGHT<=DOT_WIDTH*FILD_WIDTH;i++){
      painter.drawLine(0,i*DOT_HIGHT,FILD_HIGHT*DOT_HIGHT,i*DOT_HIGHT);
    }
}

void GameWindow::drowElements()
{
    buttExit = new QPushButton("Выход",this);
    buttExit->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-125,DOT_HIGHT*FILD_HIGHT-50),QSize(100,50)));
    score = new QLabel(this);
    score->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-125,FILD_HIGHT),QSize(100,50)));
    score->setStyleSheet(QString("font-size: %1px").arg(20));;
    score->setText("Очки: 0");
    timer = new QLabel(this);
    timer->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-136,FILD_HIGHT*3),QSize(120,60)));
    timer->setStyleSheet(QString("font-size: %1px").arg(20));;
    timer->setText("Время: 0:00");

}

void GameWindow::drowWindow()
{
    drowArea();
}
