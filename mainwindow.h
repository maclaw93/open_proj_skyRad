#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QSlider>

#include <QTimer>
#include "CutdownTimer.h"
#include <QtNetwork/QNetworkReply>
#include <QMessageBox>

#include <QDir>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPixmap>
#include <QTableView>
#include "httprequestworker.h"
#include "plane.h"
#include <QList>

#include <QTableView>
#include <QStandardItemModel>

#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void setConnections();                      ///< metoda do inicjalizacji połoczeń SIGNAL-SLOT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPixmap image;                              ///< zmienna zapamiętująca obraz
    HttpRequestWorker *worker;                  ///< wskaźnik na worker-a
    QStandardItemModel *model;                  ///< wskaźnik na model

    int searchForBeginning(int firstCountryLetterIndex, QString message);                                   ///< metoda szukająca poczatku rekordu
    int searchForEnd(int firstCountryLetterIndex, QString message);                                         ///< metoda szukająca końca rekordu
    QString selectRecord(int firstRecordLetterIndex, int lastRecordLetterIndex, QString message);           ///< metoda zwracająca rekord
    plane* parsingData(QString planeRecordData);                                                             ///< metoda zwracająca obiekt klasy plane
    bool toBoolean(QString);

    //wskazniki od wytworzenia okienka
    QWidget* _mainWidget;
    QGridLayout* _mainLayout;
    QMenuBar* _menuBar;
    QMenu* _mainManu;
    QMenu* _helpManu;
    QToolBar* _mainToolBar;
    QStatusBar* _mainStatusBar;

    //elementy GUI
    QTableView* _tabele;
    QGroupBox* _leftPart;
    QVBoxLayout* _leftPartLayout;

    QGroupBox* _timerGroup;
    QGroupBox* _displTimeGroup;
    QHBoxLayout* _timeDispLayout;
    QLabel* _timeText;
    QLabel* _timeText2;
    QLabel* _timeText3;
    QLabel* _timerInd;
    QLabel* _timeInd;
    QVBoxLayout* _timerSetLayout;
    QPushButton* _acceptTimeButton;
    QSlider* _timeSlider;
    QTimer* _timer;
    CutdownTimer* _cutdownTimer;

protected:
    QAction* actionUpdate;
    QAction* actionExite;
    QAction* actionSaveWindow;
    QAction* actionAboutApp;
    QAction* actionMinimized;

private slots:
    void updateData();                          ///< metoda aktualizujaca dane o samolotach
    void handle_result();                       ///< metoda przyjmująca odebrane dane
    void takeScreen();                          ///< metoda wykonywanie screenshot-a
    void saveScreen();                          ///< metoda do zapisywania screen-ów
    void aboutApp();                            ///< metoda do wyświetlania inforamcji o aplikacji
    void prepareTimer(int timerPeriod);
    void updateTrigged();
    void displRemaningTime();

};

#endif // MAINWINDOW_H
