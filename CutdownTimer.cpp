#include "CutdownTimer.h"
#include <QDebug>

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

void CutdownTimer::elapsStrat()
{
    timeElapsed = 0;
    emit elapsStrated();
}

void CutdownTimer::setRepetating(bool rep)
{
    isRepetating = rep;
}


bool CutdownTimer::getRepetating()
{
    return isRepetating;
}


void CutdownTimer::isElapsed()
{
    timeElapsed++;
    if((getTimeToElaps() - timeElapsed) == 0)
    {
        timeElapsed = 0;
        emit elapsed();
    }
}

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

void CutdownTimer::setTimeToElaps(int sek)
{
    _timeToElaps = sek;
}

int CutdownTimer::getTimeToElaps()
{
    return _timeToElaps;
}

int CutdownTimer::getRameining()
{
    return (timeElapsed-getTimeToElaps());
}

CutdownTimer::~CutdownTimer()
{
    qDebug() << "its the final cutdown!!!";
    this->stop();
    this->deleteLater();
}
