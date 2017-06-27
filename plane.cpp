#include "plane.h"

/*!
 * \brief plane::plane(QString icao24, QString callsign, QString originCountry, float timePosition,
 *                     float timeVelocity, float longitude, float latitude, float altitude, bool onGround,
 *                     float velocity, float heading, float verticalRate, int sensors) - konstruktor obiektu klasy plane
 *
 * - icao24 - zmienna typu QString przechowująca unikalny ICAO 24-bitowy adres transpondera w kodze hex;
 * - callsign - zmienna typu QString przechowuje 8 znakowy numer samolotu;
 * - originCountry - zmienna typu QString przechowuje nazwę kraju powiązaną z numermem ICAO;
 * - timePosition - unix timestamp (sekundy) dla ostatniej aktualizacji pozycji;
 * - timeVelocity - unix timestamp (sekundy) dla ostatniej aktualizacji prędkości;
 * - longitude - WGA-84 długość geograficzna w stopniach;
 * - latitude - WGA-84 szerokość geograficzna w stopniach;
 * - altitude - barometryczna lub geometryczna wysokość;
 * - onGround - wartość logiczna odpowiadająca stanowi samolotu na ziemi lub w powietrzu;
 * - velocity - prędkość nad ziemią w m/s;
 * - heading - kierunek samolotu w stopniach zgodnie ze wskazówkami zegara od północy;
 * - verticalRate - prędkość prostopadła do ziemi m/s (samolot sie wznosi);
 * - sensors - ID sensora wektora stanowego.
 */

plane::plane(QString icao24, QString callsign, QString originCountry, float timePosition,
             float timeVelocity, float longitude, float latitude, float altitude, bool onGround,
             float velocity, float heading, float verticalRate, int sensors)
{

    this->icao24 = icao24;
    this->callsign = callsign;
    this->originCountry = originCountry;
    this->timePosition = timePosition;
    this->timeVelocity = timeVelocity;
    this->longitude = longitude;
    this->latitude = latitude;
    this->altitude = altitude;
    this->onGround = onGround;
    this->velocity = velocity;
    this->heading = heading;
    this->verticalRate = verticalRate;
    this->sensors = sensors;

}

/*!
 * \brief plane::getIcao24() - funkcja zwraca wartości pola prywatnego icao24 klasy plane
 */

QString plane::getIcao24() const
{
    return icao24;
}

/*!
 * \brief plane::setIcao24(const QString &value) - funkcja do ustawiania wartości pola prywatnego icao24 klasy plane
 *
 * - value - referencja do stałej zmiennej typu QString
 *
 */

void plane::setIcao24(const QString &value)
{
    icao24 = value;
}

/*!
 * \brief plane::getCallsign() - funkcja zwraca wartości pola prywatnego callsign klasy plane
 */

QString plane::getCallsign() const
{
    return callsign;
}

/*!
 * \brief plane::setCallsign(const QString &value) - funkcja do ustawiania wartości pola prywatnego callsign klasy plane
 *
 * - value - referencja do stałej zmiennej typu QString
 *
 */

void plane::setCallsign(const QString &value)
{
    callsign = value;
}

/*!
 * \brief plane::getOriginCountry() - zwraca pobierania wartości pola prywatnego originCountry klasy plane
 */

QString plane::getOriginCountry() const
{
    return originCountry;
}

/*!
 * \brief plane::setOriginCountry(const QString &value) - funkcja do ustawiania wartości pola prywatnego originCountry klasy plane
 *
 * - value - referencja do stałej zmiennej typu QString
 *
 */

void plane::setOriginCountry(const QString &value)
{
    originCountry = value;
}

/*!
 * \brief plane::getTimePosition() - funkcja zwraca wartości pola prywatnego timePosition klasy plane
 */

float plane::getTimePosition() const
{
    return timePosition;
}

/*!
 * \brief plane::setTimePosition(float value) - funkcja do ustawiania wartości pola prywatnego timePosition klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setTimePosition(float value)
{
    timePosition = value;
}

/*!
 * \brief plane::getTimeVelocity() - funkcja zwraca wartości pola prywatnego timeVelocity klasy plane
 */

float plane::getTimeVelocity() const
{
    return timeVelocity;
}

/*!
 * \brief plane::setTimeVelocity(float value) - funkcja do ustawiania wartości pola prywatnego timeVelocity klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setTimeVelocity(float value)
{
    timeVelocity = value;
}

/*!
 * \brief plane::getLongitude() - funkcja zwraca wartości pola prywatnego longitude klasy plane
 */

float plane::getLongitude() const
{
    return longitude;
}

/*!
 * \brief plane::setLongitude(float value) - funkcja do ustawiania wartości pola prywatnego longitude klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setLongitude(float value)
{
    longitude = value;
}

/*!
 * \brief plane::getAltitude() - funkcja zwraca wartości pola prywatnego altitude klasy plane
 */

float plane::getAltitude() const
{
    return altitude;
}

/*!
 * \brief plane::setAltitude(float value) - funkcja do ustawiania wartości pola prywatnego altitude klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setAltitude(float value)
{
    altitude = value;
}

/*!
 * \brief plane::getOnGround() - funkcja zwraca wartości pola prywatnego onGround klasy plane
 */

bool plane::getOnGround() const
{
    return onGround;
}

/*!
 * \brief plane::setOnGround(bool value) - funkcja do ustawiania wartości pola prywatnego onGround klasy plane
 *
 * - value - zmienna typu bool do ustawienia
 *
 */

void plane::setOnGround(bool value)
{
    onGround = value;
}

/*!
 * \brief plane::getVelocity() - funkcja zwraca wartości pola prywatnego velocity klasy plane
 */

float plane::getVelocity() const
{
    return velocity;
}

/*!
 * \brief plane::setVelocity(float value) - funkcja do ustawiania wartości pola prywatnego velocity klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setVelocity(float value)
{
    velocity = value;
}

/*!
 * \brief plane::getHeading() - funkcja zwraca wartości pola prywatnego heading klasy plane
 */

float plane::getHeading() const
{
    return heading;
}

/*!
 * \brief plane::setHeading(float value) - funkcja do ustawiania wartości pola prywatnego heading klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setHeading(float value)
{
    heading = value;
}

/*!
 * \brief plane::getVerticalRate() - funkcja zwraca wartości pola prywatnego verticalRate klasy plane
 */

float plane::getVerticalRate() const
{
    return verticalRate;
}

/*!
 * \brief plane::setVerticalRate(float value) - funkcja do ustawiania wartości pola prywatnego verticalRate klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setVerticalRate(float value)
{
    verticalRate = value;
}

/*!
 * \brief plane::getSensors() - funkcja zwraca wartości pola prywatnego sensors klasy plane
 */

int plane::getSensors() const
{
    return sensors;
}

/*!
 * \brief plane::setSensors(float value) - funkcja do ustawiania wartości pola prywatnego sensors klasy plane
 *
 * - value - zmienna typu integer do ustawienia
 *
 */

void plane::setSensors(int value)
{
    sensors = value;
}

/*!
 * \brief plane::getLatitude() - funkcja zwraca wartości pola prywatnego latitude klasy plane
 */

float plane::getLatitude() const
{
    return latitude;
}

/*!
 * \brief plane::setLatitude(float value) - funkcja do ustawiania wartości pola prywatnego latitude klasy plane
 *
 * - value - zmienna typu float do ustawienia
 *
 */

void plane::setLatitude(float value)
{
    latitude = value;
}

