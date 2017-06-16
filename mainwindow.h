#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork/QNetworkReply>
#include <QMessageBox>

#include <QDir>
#include <QFileDialog>
#include <QDesktopWidget>

#include "httprequestworker.h"
#include "plane.h"
#include <QList>

#include <QTableView>
#include <QStandardItemModel>

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
    Ui::MainWindow *ui;                         ///< wyklikany interfejs użytkownika
    QPixmap image;                              ///< zmienna zapamiętująca obraz
    HttpRequestWorker *worker;                  ///< wskaźnik na worker-a
    QStandardItemModel *model;                  ///< wskaźnik na model

    int searchForBeginning(int firstCountryLetterIndex, QString message);                                   ///< metoda szukająca poczatku rekordu
    int searchForEnd(int firstCountryLetterIndex, QString message);                                         ///< metoda szukająca końca rekordu
    QString selectRecord(int firstRecordLetterIndex, int lastRecordLetterIndex, QString message);           ///< metoda zwracająca rekord
    plane* parsingData(QString planeRecordData);                                                             ///< metoda zwracająca obiekt klasy plane
    bool toBoolean(QString);

private slots:
    void updateData();                          ///< metoda aktualizujaca dane o samolotach
    void handle_result();                       ///< metoda przyjmująca odebrane dane
    void takeScreen();                          ///< metoda wykonywanie screenshot-a
    void saveScreen();                          ///< metoda do zapisywania screen-ów
    void aboutApp();                            ///< metoda do wyświetlania inforamcji o aplikacji

};

#endif // MAINWINDOW_H
