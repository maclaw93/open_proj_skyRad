#include "CutdownTimer.h"
#include <QDebug>

/*!
 *  \brief CutdownTimer::CutdownTimer - konstruktor klasy. W ciele znajdują się połączenia sygnałów i slotów, ustanienia powtarzania i czasu do odliczania.
 *  \param parent - wskaznik na obiekt nadrzędny.
 *  \param sek - nastawa czasu dla licznika, wyrażana w sekundach.
 *  \param repetative - flaga do zapętlania licznika
 *
 */

CutdownTimer::CutdownTimer(QObject *parent, int sek, bool repetative) :
    QTimer(parent)
{
    this->setInterval(1000);
    qDebug() << "ElapsTimer created, his id: " << this->timerId();
    setRepetating(repetative);
    setTimeToElaps(sek);

    connect(this, SIGNAL(elapsStrated()),
            this, SLOT(start()));
    connect(this, SIGNAL(timeout()),
            this, SLOT(isElapsed()));
    connect(this, SIGNAL(elapsed()),
            this, SLOT(elapsStop()));
}

/*!
 * \brief CutdownTimer::elapsStrat() - metoda wyzwalająca licznik czasu
 */

void CutdownTimer::elapsStrat()
{
    timeElapsed = 0;
    emit elapsStrated();
}

/*!
 * \brief CutdownTimer::setRepetating() - metoda ustawiająca flage zapętlenia licznika
 */

void CutdownTimer::setRepetating(bool rep)
{
    isRepetating = rep;
}

/*!
 * \brief CutdownTimer::getRepetating() -metoda zwracająca flagę zapętlenia licznika
 */

bool CutdownTimer::getRepetating()
{
    return isRepetating;
}

/*!
 * \brief CutdownTimer::isElapsed() - funckja do odliczania czasu
 */

void CutdownTimer::isElapsed()
{
    timeElapsed++;
    if((getTimeToElaps() - timeElapsed) == 0)
    {
        timeElapsed = 0;
        emit elapsed();
    }
}

/*!
 * \brief CutdownTimer::elapsStop() - funkcja do sprawdzania cykli odliczania
 */

void CutdownTimer::elapsStop()
{
    if(!getRepetating())
    {
        qDebug() << "its over";
        this->stop();
    }
    else
    {
        qDebug() << "new round";
    }
}

/*!
 * \brief CutdownTimer::setTimeToElaps(int sek) - funkcja ustawiająca czas do odliczania
 *
 * \param sek - zmienna typu integer zawierająca ilość sekund do odliczania
 */

void CutdownTimer::setTimeToElaps(int sek)
{
    _timeToElaps = sek;
}

/*!
 * \brief CutdownTimer::getTimeToElaps() - funkcja pobierająca czas do odliczania
 */

int CutdownTimer::getTimeToElaps()
{
    return _timeToElaps;
}

/*!
 * \brief CutdownTimer::getRameining() - funkcja pobierjąca czas pozostały do odlicznia
 */

int CutdownTimer::getRameining()
{
    return (timeElapsed-getTimeToElaps());
}

/*!
 * \brief CutdownTimer::~CutdownTimer() - destruktor
 */

CutdownTimer::~CutdownTimer()
{
    qDebug() << "its the final cutdown!!!";
    this->stop();
    this->deleteLater();
}
