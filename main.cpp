#include "mainwindow.h"

#include <QApplication>

/*!
\mainpage Radiator Serwerowy wyswietlajacy dynamicznie inforamcje "SkyRad"
\author Michał Kluska & Maciek Kucharski
\date 27.06.17
\version 1.0
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow ww;

    ww.showFullScreen();

    return a.exec();
}
