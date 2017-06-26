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

/*! Klasa MainWindow - odpowiada wygląd głownego okna programu, budowe layout-u, połączenie elementów okna z metodami
 *
 * W obrębie klasy wykonywane są wszystkie działania związane z działaniami w głównym oknie programu.
 *
 *
 * Klasa posiada:
 * chronione sloty - pozwalające na otrzymywanie inforamcji
 * signały - do przesyłania danych do metod i innych klas
 * zmienne oraz wskażniki prywatne - potrzebne do poprawnego działania metod klasy oraz wywoływania
 * chronione funkcje - odpowiadające za akcje wewnątrz klasy
 * konstruktor jawny

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
    HttpRequestWorker *worker;                  ///< wskaźnik na worker-a
    QStandardItemModel *model;                  ///< wskaźnik na model
    bool isFirstTime;                           ///< zmienna poczatkowa inicjacyjna pobieranie danych

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
    QMenu* _helpManu;           ///< wskaźnik na menu pomicy
    QToolBar* _mainToolBar;     ///< wskaźnik na pasek narzędzi
    QStatusBar* _mainStatusBar; ///< wskażnik na pasek statusu

    //elementy GUI

    QTableView* _tabele;            ///< wskażnik na tabele
    QGroupBox* _leftPart;           ///< wskażnik na groupbox-a w lewej części okna
    QVBoxLayout* _leftPartLayout;   ///< wskażnik na lewą część layout-a

    QGroupBox* _timerGroup;         ///< wskażnik na groupbox-a panelu czasu
    QGroupBox* _displTimeGroup;     ///< wskażnik na groupbox-a do wyświetlania czasu
    QHBoxLayout* _timeDispLayout;   ///< wskażnik na layout z wyświetlaniem czasu
    QLabel* _timeText;              ///< wskażnik na etykiete czasu
    QLabel* _timeText2;             ///< wskażnik na etykiete czasu 1
    QLabel* _timeText3;             ///< wskażnik na etykiete czasu 2
    QLabel* _timerInd;              ///< wskażnik na etykiete interału zegara
    QLabel* _timeInd;               ///< wskażnik na etykiete interału czasu
    QVBoxLayout* _timerSetLayout;   ///< wskażnik na layout z elementami zegara
    QPushButton* _acceptTimeButton; ///< wskażnik na przycisk do akceptacji czasu
    QSlider* _timeSlider;           ///< wskażnik na suwak do zmiany czasu
    QTimer* _timer;                 ///< wskażnik na zegar
    CutdownTimer* _cutdownTimer;    ///< wskażnik na liczący w dół

protected:
    QAction* actionUpdate;          ///< wskażnik na przycisk menu z akcją aktualizacji
    QAction* actionExite;           ///< wskażnik na przycisk menu z akcją wyjścia
    QAction* actionSaveWindow;      ///< wskażnik na przycisk menu z akcją zapisu zrzutu okna
    QAction* actionAboutApp;        ///< wskażnik na przycisk menu z akcją o aplikacji
    QAction* actionMinimized;       ///< wskażnik na przycisk menu z akcja minimalizacji okna

private slots:
    void updateData();                          ///< metoda aktualizujaca dane o samolotach
    void handle_result();                       ///< metoda przyjmująca odebrane dane
    void takeScreen();                          ///< metoda wykonywanie screenshot-a
    void saveScreen();                          ///< metoda do zapisywania screen-ów
    void aboutApp();                            ///< metoda do wyświetlania inforamcji o aplikacji
    void prepareTimer();                        ///< metoda do przygotowyania zegara
    void updateTrigged();                       ///< metoda do aktualizacji wyzwalania
    void displRemaningTime();                   ///< metoda do wyświetlania pozostałego czasu

signals:
    void go();

};

#endif // MAINWINDOW_H
