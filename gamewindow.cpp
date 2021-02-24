#include "gamewindow.h"

GameWindow::GameWindow()
{
    setFocus();

    resize(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH,DOT_HIGHT*FILD_HIGHT);
    this->setWindowTitle("TwoPythons");

    drowElements();
    socket=new QTcpSocket(this);

    socket->connectToHost("192.168.9.4",58);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockConnect()));
    char str[100];
    std::string str2="{\"globalType\":\"connection\",\"type\":\"test\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    repaint();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{

    std::string strCallback;
    char str[100];
    int key=event->key();
    switch (key) {
    case Qt::Key_Left:
        qDebug()<<"left";
        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"left\"}\r\n\r\n";
        break;
    case Qt::Key_Right:
        qDebug()<<"right";
        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"right\"}\r\n\r\n";
        break;
    case Qt::Key_Down:
        qDebug()<<"down";
         strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"down\"}\r\n\r\n";
        break;

    case Qt::Key_Up:
        qDebug()<<"up";
        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"up\"}\r\n\r\n";
        break;


    }
    strcpy(str,strCallback.c_str());
    socket->write(str);

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


void GameWindow::drowPython(QVector<QPoint>inDots,Qt::GlobalColor color)
{
    QPainter painter(this);
     painter.setBrush(color);
    for(int i=0;i<inDots.size();i++){
       painter.drawRect(QRect(DOT_HIGHT*inDots[i].rx(), DOT_WIDTH*inDots[i].ry(), DOT_WIDTH, DOT_HIGHT));

    }

}

void GameWindow::drowFruits()
{
    QPainter painter(this);
     painter.setBrush((QBrush(Qt::green)));

    for(int i=0;i<fruits.size();i++){

       painter.drawRect(QRect(DOT_HIGHT*fruits[i].rx(), DOT_WIDTH*fruits[i].ry(), DOT_WIDTH, DOT_HIGHT));

    }


}

void GameWindow::sockConnect()
{


    data = QString(socket->readLine()).trimmed();

    doc=QJsonDocument::fromJson(data.toUtf8(),&docERR);
    QPoint teamp;
    if(docERR.errorString()=="no error occurred")
    {

        if(doc.object().value(("type")).toString()=="setDisplay"){
            QJsonArray docArOne=doc.object().value("coordinatesPython1").toArray();
            QJsonArray docArThree=doc.object().value("coordinatesPython2").toArray();
            QJsonArray docArTwo=doc.object().value("coordinatesFruits").toArray();
            for(int i=0;i<docArOne.count();i++)
            {
              teamp.rx()=docArOne[i].toObject().value("x").toString().toInt();
              teamp.ry()=docArOne[i].toObject().value("y").toString().toInt();
              dots.append(teamp);
            }
            for(int i=0;i<docArThree.count();i++)
            {
              teamp.rx()=docArThree[i].toObject().value("x").toString().toInt();
              teamp.ry()=docArThree[i].toObject().value("y").toString().toInt();
              dots2.append(teamp);
            }
            for(int i=0;i<docArTwo.count();i++)
            {
              teamp.rx()=docArTwo[i].toObject().value("x").toString().toInt();
              teamp.ry()=docArTwo[i].toObject().value("y").toString().toInt();
              fruits.append(teamp);
            }

        }

        repaint();
        dots.clear();
        dots2.clear();
        fruits.clear();
    }
}


void GameWindow::drowWindow()
{
    drowArea();
    drowFruits();
    drowPython(dots,Qt::red);
    drowPython(dots2,Qt::blue);

}
