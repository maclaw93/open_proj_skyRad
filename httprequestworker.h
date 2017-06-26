#ifndef HTTPREQUESTWORKER_H
#define HTTPREQUESTWORKER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

/*! Klasa HttpRequestInputFileElement - odpowiada za przechowanie inforamcji plikach wymiany
 *
 * Klasa posiada:
 *
 * publiczne: pola danych

    Michał Kluska & Maciek Kucharski, czerwiec 2017

*/

enum HttpRequestVarLayout {NOT_SET, ADDRESS, URL_ENCODED, MULTIPART}; ///< definicja typów wyliczniowych


class HttpRequestInputFileElement {

public:
    QString variable_name;      ///< zmienna przechwująca nazwę zmiennej
    QString local_filename;     ///< zmienna przechowująca nazwę lokalnego pliku
    QString request_filename;   ///< zmienna przechowująca nazwę pliku rządanego
    QString mime_type;          ///< zmienna przechowujaća typ mime

};

/*! Klasa HttpRequestInput - odpowiada rządanie Http
 *
 * W obrębie klasy wykonywane są wszystkie działania związane z komunikacją aplikacji z serwerem i pobieraniem danych
 *
 *
 * Klasa posiada:
 * publiczne: pola oraz metody
 * konstruktor jawny

    Michał Kluska & Maciek Kucharski, czerwiec 2017

*/

class HttpRequestInput {

public:
    QString url_str;                            ///< zmienna przechwująca adres url
    QString http_method;                        ///< zmienna przechwująca metodę  http
    HttpRequestVarLayout var_layout;            ///< zmienna przechwująca zmienna layout-a
    QMap<QString, QString> vars;                ///< QMap-a zawierajaca pola QString
    QList<HttpRequestInputFileElement> files;   ///< Lista typu HttpRequestInputFileElement

    HttpRequestInput();                                         ///< konstruktor bez parametryczny
    HttpRequestInput(QString v_url_str, QString v_http_method); ///< konstruktor parametryczny
    void initialize();                                          ///< metoda inicjalizacji
    void add_var(QString key, QString value);                   ///< metoda dodajaca arkumenty zapytania
    void add_file(QString variable_name, QString local_filename, QString request_filename, QString mime_type); ///< metoda dodająca pliki

};

/*! Klasa HttpRequestWorker - odpowiada za tworzenie workera wykonującego zapytania
 *
 *
 * Klasa posiada:
 * - publiczne pola oraz metody
 * - prywatne pola oraz metody
 * - prywatne sloty
 * - sygnały
 * - konstruktor jawny

    Michał Kluska & Maciek Kucharski, czerwiec 2017

*/

class HttpRequestWorker : public QObject {
    Q_OBJECT

public:
    QByteArray response;                            ///< zmienna odpowiedzi
    QNetworkReply::NetworkError error_type;         ///< zmienna błędu połaczenia
    QString error_str;                              ///< zmienna kounikatu błedu

    explicit HttpRequestWorker(QObject *parent = 0);    ///< konstruktor jawny

    QString http_attribute_encode(QString attribute_name, QString input);   ///< metoda zwracjąca QStrning z atrybutami kodowania
    void execute(HttpRequestInput *input);                                  ///< metoda wykonujaca zapytanie

signals:
    void on_execution_finished(HttpRequestWorker *worker);          ///< metoda na zakonczenie wykonania zapytania

private:
    QNetworkAccessManager *manager;                     ///< wskaźnik na obiekt klasy QNetworkAccessManager

private slots:
    void on_manager_finished(QNetworkReply *reply);     ///< metoda wywoływana na koniec pracy menadżera

};

#endif // HTTPREQUESTWORKER_H
