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

/*! Klasa MainWindow - odpowiada za wygląd głownego okna programu, budowe layout-u, połączenie elementów okna z metodami.
 *
 * W obrębie klasy wykonywane są wszystkie działania związane z działaniami w głównym oknie programu. Stanowi ona
 * UI dla użytkownika.
 *
 * Klasa posiada:
 * prywatne sloty - pozwalające na otrzymywanie inforamcji;
 * signały - do przesyłania danych do metod i innych klas;
 * zmienne oraz wskażniki prywatne - potrzebne do poprawnego działania metod klasy oraz wywoływania;
 * chronione funkcje - odpowiadające za akcje wewnątrz klasy;
 * konstruktor jawny.

    Michał Kluska & Maciek Kucharski, czerwiec 2017

*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void setConnections();                      ///< metoda do inicjalizacji połoczeń SIGNAL-SLOT

public:
    MainWindow(QWidget *parent = 0);            ///< konstruktor obiektu klasy MainWindow
    ~MainWindow();                              ///< destruktor obiektu klasy MainWindow

private:
    QPixmap image;                              ///< zmienna zapamiętująca obraz
    HttpRequestWorker *worker;                  ///< wskaźnik na worker-a obsługujący zapytania REST
    QStandardItemModel *model;                  ///< wskaźnik na model danych wyświetlanych w tabeli
    bool isFirstTime;                           ///< zmienna początkowa inicjująca pobieranie danych

    int searchForBeginning(int firstCountryLetterIndex, QString message);                                   ///< metoda szukająca poczatku rekordu
    int searchForEnd(int firstCountryLetterIndex, QString message);                                         ///< metoda szukająca końca rekordu
    QString selectRecord(int firstRecordLetterIndex, int lastRecordLetterIndex, QString message);           ///< metoda zwracająca rekord
    plane* parsingData(QString planeRecordData);                                                            ///< metoda zwracająca obiekt klasy plane uzupełniony parametrami
    bool toBoolean(QString);                                                                                ///< metoda konwertująca wartość typu QString na wartość logiczną typu bool

    //wskazniki od wytworzenia okienka

    QWidget* _mainWidget;       ///< wskaźnik na główny widget
    QGridLayout* _mainLayout;   ///< wskaźnik na główny layout
    QMenuBar* _menuBar;         ///< wskaźnik na pasek menu
    QMenu* _mainManu;           ///< wskaźnik na menu główne
    QMenu* _helpManu;           ///< wskaźnik na menu pomocy

    //elementy GUI

    QTableView* _tabele;            ///< wskaźnik na tabelę danych
    QGroupBox* _rightPart;           ///< wskaźnik na groupbox-a w prawej części okna
    QVBoxLayout* _rightPartLayout;   ///< wskaźnik na prawą część layout-u

    QGroupBox* _timerGroup;         ///< wskaźnik na groupbox-a panelu czasu
    QGroupBox* _displTimeGroup;     ///< wskaźnik na groupbox-a do wyświetlacza nastawy czasu odświeżnia
    QHBoxLayout* _timeDispLayout;   ///< wskaźnik na layout z wyświetlaniem nastawy czasu odświeżnia
    QLabel* _timeText;              ///< wskaźnik na etykiete czasu
    QLabel* _timeText2;             ///< wskaźnik na etykiete czasu 2
    QLabel* _timeText3;             ///< wskaźnik na etykiete czasu 3
    QLabel* _timerInd;              ///< wskaźnik na etykiete wyświetlacza czasu do kolejnego odświeżania
    QLabel* _timeInd;               ///< wskaźnik na etykiete wyświetlania interału czasu odświeżania
    QVBoxLayout* _timerSetLayout;   ///< wskaźnik na layout z elementami zegara
    QPushButton* _acceptTimeButton; ///< wskaźnik na przycisk do akceptacji czasu
    QSlider* _timeSlider;           ///< wskaźnik na suwak do zmiany czasu
    QTimer* _timer;                 ///< wskaźnik na zegar
    CutdownTimer* _cutdownTimer;    ///< wskażnik na licznik liczący w dół

protected:
    QAction* actionUpdate;          ///< wskaźnik na przycisk menu z akcją aktualizacji
    QAction* actionExite;           ///< wskaźnik na przycisk menu z akcją wyjścia
    QAction* actionSaveWindow;      ///< wskaźnik na przycisk menu z akcją zapisu zrzutu okna
    QAction* actionAboutApp;        ///< wskaźnik na przycisk menu z akcją o aplikacji
    QAction* actionMinimized;       ///< wskaźnik na przycisk menu z akcja minimalizacji okna

private slots:
    void updateData();                          ///< metoda aktualizująca dane o samolotach
    void handle_result();                       ///< metoda przyjmująca odebrane dane
    void takeScreen();                          ///< metoda do wykonywania screenshot-a
    void saveScreen();                          ///< metoda do zapisywania screen-ów
    void aboutApp();                            ///< metoda do wyświetlania inforamcji o aplikacji
    void prepareTimer();                        ///< metoda do przygotowyania zegara
    void updateTrigged();                       ///< metoda do wyzwalania aktualizacji
    void displRemaningTime();                   ///< metoda do wyświetlania pozostałego czasu

signals:
    void go();                                  ///< sygnał uruchamiający timery

};

#endif // MAINWINDOW_H
