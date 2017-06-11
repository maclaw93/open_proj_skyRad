#include "mainGUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGUI ww;
    ww.show();
    //ww.showFullScreen();

    return a.exec();
}
