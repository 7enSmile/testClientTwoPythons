#include <iostream>
#include <gamewindow.h>
#include <QApplication>
using namespace std;

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    GameWindow game;
    game.show();
    return app.exec();
}
