#ifndef CUTDOWNTIMER_H
#define CUTDOWNTIMER_H

#include <QTimer>

/*! Klasa CutdownTimer - odpowiada za dostarczenie licznika czasu.
 *
 * W obrębie klasy wykonywane są działania na zegarze. Rozszerza funkcjonalności klasy QTimer.
 *
 *
 * Klasa posiada:
 * prywatne sloty - pozwalające na otrzymywanie inforamcji
 * signały - do przesyłania danych do metod i innych klas
 * zmienne oraz wskaźniki prywatne - potrzebne do poprawnego działania metod klasy oraz wywoływania
 * prywatne funkcje - odpowiadające za akcje wewnątrz klasy
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
    void setRepetating(bool rep);                                       ///< metoda ustawiająca zapętlenie licznika
    bool getRepetating();                                               ///< metoda pobierająca zapętlenie licznika
    int timeElapsed;                                                    ///< zmienna przechowywująca czas do odliczenia

private:
    int _timeToElaps;               ///< zmienna przechowujaca czas do zakonczenia odlicznia
    bool isRepetating;              ///< zmienna przechowujaca watość logiczną zapętlenia licznika

signals:
    void elapsed();                 ///< sygnał wskazujący upłynięcie czasu
    void elapsStrated();            ///< sygnał wyzwalający licznik czasu

public slots:
    void elapsStop();               ///< metoda do zakonczenia odliczania
    void elapsStrat();              ///< metoda do rozpoczęcia odlicznia

private slots:
    void isElapsed();               ///< metoda do sprawdzania odliczania czasu

};

#endif // CUTDOWNTIMER_H
