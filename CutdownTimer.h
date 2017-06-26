#ifndef CUTDOWNTIMER_H
#define CUTDOWNTIMER_H

#include <QTimer>

/*! Klasa CutdownTimer - odpowiada za działanie zegara
 *
 * W obrębie klasy wykonywane działania na zegarze.
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

class CutdownTimer : public QTimer
{
    Q_OBJECT

public:
    explicit CutdownTimer(QObject *parent = 0, int = 5, bool = false);  ///< konstruktor parametryczny bez automatycznej konwersji obiektu klasy CutdownTimer
    ~CutdownTimer();                                                    ///< destruktor obiektu klasy CutdownTimer
    void setTimeToElaps(int sek);                                       ///< metoda ustawiająca czas do odliczania
    int getTimeToElaps();                                               ///< metoda pobierająca czas do odliczania
    int getRameining();                                                 ///< metoda pobierająca pozostały czas do odliczania
    void setRepetating(bool rep);                                       ///< metoda ustawiająca powtarzanie zegara
    bool getRepetating();                                               ///< metoda pobierająca powtarzanie zegara
    int timeElapsed;                                                    ///< zmienna przechwowujaca czas do odliczenia

private:
    int _timeToElaps;               ///< zmienna przechowujaca czas do zakonczenia odlicznia
    bool isRepetating;              ///< zmienna przechowujaca watość logiczną kontynuacja odliczania

signals:
    void elapsed();                 ///<
    void elapsStrated();            ///<

public slots:
    void elapsStop();               ///< metoda do zakonczenia odliczania
    void elapsStrat();              ///< metoda do rozpoczęcia odlicznia

private slots:
    void isElapsed();               ///< metoda do sprawdzania odliczania czasu

};

#endif // CUTDOWNTIMER_H
