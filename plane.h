#ifndef PLANE_H
#define PLANE_H

#include <QString>

class plane
{
public:
    plane(QString icao24, QString callsign, QString originCountry, float timePosition, float timeVelocity, float longitude, float latitude, float altitude, bool onGround, float velocity, float heading, float verticalRate, int sensors);


    QString getIcao24() const;
    void setIcao24(const QString &value);

    QString getCallsign() const;
    void setCallsign(const QString &value);

    QString getOriginCountry() const;
    void setOriginCountry(const QString &value);

    float getTimePosition() const;
    void setTimePosition(float value);

    float getTimeVelocity() const;
    void setTimeVelocity(float value);

    float getLongitude() const;
    void setLongitude(float value);

    float getAltitude() const;
    void setAltitude(float value);

    bool getOnGround() const;
    void setOnGround(bool value);

    float getVelocity() const;
    void setVelocity(float value);

    float getHeading() const;
    void setHeading(float value);

    float getVerticalRate() const;
    void setVerticalRate(float value);

    int getSensors() const;
    void setSensors(int value);

private:
    QString icao24;
    QString callsign;
    QString originCountry;
    float timePosition;
    float timeVelocity;
    float longitude;
    float latitude;
    float altitude;
    bool onGround;
    float velocity;
    float heading;
    float verticalRate;
    int sensors;
};

#endif // PLANE_H
