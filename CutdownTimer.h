#ifndef CUTDOWNTIMER_H
#define CUTDOWNTIMER_H

#include <QTimer>

class CutdownTimer : public QTimer
{
    Q_OBJECT

public:
    explicit CutdownTimer(QObject *parent = 0, int = 5, bool = false);
    ~CutdownTimer();
    void setTimeToElaps(int sek);
    int getTimeToElaps();
    int getRameining();
    void setRepetating(bool rep);
    bool getRepetating();
    int timeElapsed;

private:
    int _timeToElaps;
    bool isRepetating;

signals:
    void elapsed();
    void elapsStrated();

public slots:
    void elapsStop();
    void elapsStrat();

private slots:
    void isElapsed();

};

#endif // CUTDOWNTIMER_H
