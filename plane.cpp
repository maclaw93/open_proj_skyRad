#include "plane.h"

plane::plane()
{
}
QString plane::getIcao24() const
{
    return icao24;
}

void plane::setIcao24(const QString &value)
{
    icao24 = value;
}
QString plane::getCallsign() const
{
    return callsign;
}

void plane::setCallsign(const QString &value)
{
    callsign = value;
}
QString plane::getOriginCountry() const
{
    return originCountry;
}

void plane::setOriginCountry(const QString &value)
{
    originCountry = value;
}
float plane::getTimePosition() const
{
    return timePosition;
}

void plane::setTimePosition(float value)
{
    timePosition = value;
}
float plane::getTimeVelocity() const
{
    return timeVelocity;
}

void plane::setTimeVelocity(float value)
{
    timeVelocity = value;
}
float plane::getLongitude() const
{
    return longitude;
}

void plane::setLongitude(float value)
{
    longitude = value;
}
float plane::getAltitude() const
{
    return altitude;
}

void plane::setAltitude(float value)
{
    altitude = value;
}
bool plane::getOnGround() const
{
    return onGround;
}

void plane::setOnGround(bool value)
{
    onGround = value;
}
float plane::getVelocity() const
{
    return velocity;
}

void plane::setVelocity(float value)
{
    velocity = value;
}
float plane::getHeading() const
{
    return heading;
}

void plane::setHeading(float value)
{
    heading = value;
}
float plane::getVerticalRate() const
{
    return verticalRate;
}

void plane::setVerticalRate(float value)
{
    verticalRate = value;
}
int plane::getSensors() const
{
    return sensors;
}

void plane::setSensors(int value)
{
    sensors = value;
}
















