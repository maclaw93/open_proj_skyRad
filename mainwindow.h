#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork/QNetworkReply>
#include <QMessageBox>

#include <QDir>
#include <QFileDialog>
#include <QDesktopWidget>

#include "httprequestworker.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void setConnections();                      ///< metoda do inicjalizacji połoczeń SIGNAL-SLOT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap image;                              ///<zmienna zapamiętująca obraz

private slots:
    void updateData();
    void handle_result(HttpRequestWorker *worker);
    void takeScreen();                          ///< metoda wykonywanie screenshot-a
    void saveScreen();                          ///< metoda do zapisywania screen-ów
    void aboutApp();                            ///< metoda do wyświetlania inforamcji o aplikacji

};

#endif // MAINWINDOW_H
