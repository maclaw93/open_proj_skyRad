#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow ww;
    //ww.show();
    ww.showFullScreen();

    return a.exec();
}
