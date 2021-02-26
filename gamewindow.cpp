#include "gamewindow.h"

GameWindow::GameWindow()
{
    setFocus();

    resize(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH,DOT_HIGHT*FILD_HIGHT);
    this->setWindowTitle("TwoPythons");

    drowElements();
    socket=new QTcpSocket(this);

    socket->connectToHost("127.0.0.1",58);
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

        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"left\"}\r\n\r\n";
        break;
    case Qt::Key_Right:

        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"right\"}\r\n\r\n";
        break;
    case Qt::Key_Down:

         strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"down\"}\r\n\r\n";
        break;

    case Qt::Key_Up:

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
    buttExit->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-150,DOT_HIGHT*FILD_HIGHT-70),QSize(100,50)));
    score = new QLabel(this);
    score->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-150,FILD_HIGHT),QSize(100,50)));
    score->setStyleSheet(QString("font-size: %1px").arg(20));;
    score->setText("Очки: 0");
    timer = new QLabel(this);
    timer->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-150,FILD_HIGHT*3),QSize(120,60)));
    timer->setStyleSheet(QString("font-size: %1px").arg(20));;
    timer->setText("Время: 0:00");
    preparation=new QLabel(this);
    preparation->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-110,FILD_HIGHT*10),QSize(60,120)));
    preparation->setStyleSheet(QString("font-size: %1px").arg(40));;
    preparation->setText("7");


}


void GameWindow::drowPythons()
{
    for(int i=0;i<pythons.size();i++){

        QPainter painter(this);
        QBrush brush;

       painter.setBrush(QBrush(pythons[i]->color));
       for(int j=0;j<pythons[i]->dots.size();j++){

            painter.drawRect(QRect(DOT_HIGHT*pythons[i]->dots[j].rx(), DOT_WIDTH*pythons[i]->dots[j].ry(), DOT_WIDTH, DOT_HIGHT));

       }

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
    if(socket->waitForConnected(50)){


    data = QString(socket->readLine()).trimmed();




    doc=QJsonDocument::fromJson(data.toUtf8(),&docERR);
    QPoint teamp;

    if(docERR.errorString()=="no error occurred")
    {

        if(doc.object().value(("type")).toString()=="setDisplay"){
            QJsonArray docArPythons=doc.object().value("pythons").toArray();
            QJsonArray docArPythonCoords;
            QJsonArray docArPythonCoolor;

            QJsonArray docArFruits=doc.object().value("coordinatesFruits").toArray();
            for(int i=0;i<docArPythons.count();i++){
                docArPythonCoords=docArPythons[i].toObject().value("coordinates").toArray();
                docArPythonCoolor=docArPythons[i].toObject().value("color").toArray();
                Python *python=new Python();
                for(int j=0;j< docArPythonCoords.count();j++){
                    teamp.rx()=docArPythonCoords[j].toObject().value("x").toString().toInt();
                    teamp.ry()=docArPythonCoords[j].toObject().value("y").toString().toInt();
                    python->dots.append(teamp);


                }

                python->color.setRgb(docArPythonCoolor[0].toString().toInt(),docArPythonCoolor[1].toString().toInt(),docArPythonCoolor[2].toString().toInt());

                pythons.append(python);


            }
            for(int i=0;i<docArFruits.count();i++)
            {
              teamp.rx()=docArFruits[i].toObject().value("x").toString().toInt();
              teamp.ry()=docArFruits[i].toObject().value("y").toString().toInt();
              fruits.append(teamp);
            }

        }
        if(doc.object().value(("type")).toString()=="prepareTimer"){
            preparation->setText(doc.object().value(("time")).toString());
            if(doc.object().value(("time")).toString().toInt()==0){
                preparation->setText("");
                startGame=true;
            }

        }
        score->setText("Очки: "+doc.object().value("points").toString());
        repaint();
        if(startGame){
        pythons.clear();
        fruits.clear();
        }

    }
    }
}


void GameWindow::drowWindow()
{

    drowArea();
    drowFruits();
    drowPythons();


}
