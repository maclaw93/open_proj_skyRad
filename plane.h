#ifndef PLANE_H
#define PLANE_H

#include <QString>

/*! Klasa Plane - obiekt reprezentujący dane na temat samolotu.
 *
 * Klasa stanowi zbiór danych na temat pojedyńczego samolotu, uzyskanych po obróbce odpowiedzi
 * na zapytanie GET z interfejsu REST.
 *
 *
 * Klasa posiada:
 * publiczne funkcje - pozwalające na ustawienie/pobrabnie inforamcji;
 * prywatne zmienne - przechowywujące dane danego samolotu.

    Michał Kluska & Maciek Kucharski, czerwiec 2017

*/


class plane
{
public:
    plane(QString icao24, QString callsign, QString originCountry, float timePosition,
          float timeVelocity, float longitude, float latitude, float altitude, bool onGround,
          float velocity, float heading, float verticalRate, int sensors);                  ///< konstruktor obiektu

    QString getIcao24() const;                  ///< metoda do odczytu zmiennej prywatnej icao24
    void setIcao24(const QString &value);

    QString getCallsign() const;                ///< metoda do odczytu zmiennej prywatnej callsign
    void setCallsign(const QString &value);

    QString getOriginCountry() const;           ///< metoda do odczytu zmiennej prywatnej originCountry
    void setOriginCountry(const QString &value);

    float getTimePosition() const;              ///< metoda do odczytu zmiennej prywatnej timePosition
    void setTimePosition(float value);

    float getTimeVelocity() const;              ///< metoda do odczytu zmiennej prywatnej timeVelocity
    void setTimeVelocity(float value);

    float getLongitude() const;                 ///< metoda do odczytu zmiennej prywatnej longitude
    void setLongitude(float value);

    float getLatitude() const;                  ///< metoda do odczytu zmiennej prywatnej latitude
    void setLatitude(float value);

    float getAltitude() const;                  ///< metoda do odczytu zmiennej prywatnej altitude
    void setAltitude(float value);

    bool getOnGround() const;                   ///< metoda do odczytu zmiennej prywatnej onGround
    void setOnGround(bool value);

    float getVelocity() const;                  ///< metoda do odczytu zmiennej prywatnej velocity
    void setVelocity(float value);

    float getHeading() const;                   ///< metoda do odczytu zmiennej prywatnej heading
    void setHeading(float value);

    float getVerticalRate() const;              ///< metoda do odczytu zmiennej prywatnej verticalRate
    void setVerticalRate(float value);

    int getSensors() const;                     ///< metoda do odczytu zmiennej prywatnej sensors
    void setSensors(int value);


private:
    QString icao24;                 ///< pole przechowujące unikalny ICAO 24-bitowy adres transpondera w kodze hex
    QString callsign;               ///< pole przechowujące 8 znakowy numer samolotu
    QString originCountry;          ///< pole przechowujące nazwę kraju powizanego z numerem ICAO
    float timePosition;             ///< pole przechowujące unix timestamp (sekundy) dla ostatniej aktualiazji pozycji
    float timeVelocity;             ///< pole przechowujące unix timestamp (sekundy) dla ostatniej aktualizacji prędkości
    float longitude;                ///< pole przechowujące WGA-84 długość geograficzną w stopniach
    float latitude;                 ///< pole przechowujące WGA-84 szerokość geograficzną w stopniach
    float altitude;                 ///< pole przechowujące barometryczna lub geometryczna wysokość
    bool onGround;                  ///< pole przechowujące wartość logiczną, odpowiadającą stanowi samolotu na ziemi lub w powietrzu
    float velocity;                 ///< pole przechowujące prędkość nad ziemią w m/s
    float heading;                  ///< pole przechowujące kierunek samolotu w stopniach zgodnie ze wskazówkami zegara od północy
    float verticalRate;             ///< pole przechowujące prędkość prostopadłą do ziemi w m/s (samolot się wznosi)
    int sensors;                    ///< pole przechowujące ID sensora wektora stanowego

};

#endif // PLANE_H
