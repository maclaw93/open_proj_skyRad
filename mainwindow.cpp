#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    worker = new HttpRequestWorker(this);
    setConnections();
}

/*!
 * \brief MainWindow::~MainWindow() - destruktory
 */

MainWindow::~MainWindow()
{
    delete ui;
    delete worker;
}

/*!
 * \brief MainWindow::setConnections() - funkcja zawierająca sygnały i sloty
 */

void MainWindow::setConnections()
{
    connect(ui->actionUpdate, SIGNAL(triggered()),                      // połączenie przycisku z menu z metodą aktualizuj dane
            this, SLOT(updateData()));
    connect(ui->actionExit, SIGNAL(triggered()),                        // połączenie przycisku z menu z metodą zamykajacą aplikację
            this, SLOT(close()));
    connect(ui->actionSaveWindow, SIGNAL(triggered()),                  // połączenie przycisku z menu z metodą wykonującą zrzut ekranu
            this, SLOT(takeScreen()));
    connect(ui->actionAboutApp, SIGNAL(triggered()),                    // połączenie przycisku z menu z metodą wyświetlającą informację o aplikacji
            this, SLOT(aboutApp()));
    connect(ui->actionAboutQt, SIGNAL(triggered()),                     // połączenie przycisku z menu z metodą wyświetlajacą informacje o Qt
            qApp, SLOT(aboutQt()));
    connect(ui->actionMinimize, SIGNAL(triggered()),                    // połączenie przycisku z menu z metodą minimalizującą okno
            this, SLOT(showMinimized()));
    connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)),  // połaczenie worker-a z metodą odbierajaca dane
            this, SLOT(handle_result()));
}

/*!
 * \brief MainWindow::updateData() - funkcja wykonująca zapytanie GET
 */

void MainWindow::updateData()
{
    QString url_str = "https://opensky-network.org/api/states/all";

    HttpRequestInput input(url_str, "GET");

    //input.add_var("lon", "100.75");
    //input.add_var("lat", "1.5");
    //input.add_var("begin", "2014-02-01");
    //input.add_var("api_key", "DEMO_KEY");

    worker->execute(&input);
}

/*!
 * \brief MainWindow::handle_result(HttpRequestWorker *worker) - funkcja wyłapuje odpowiedź
 *
 *
 * - worker - wskaźnik na połączenie
 */

void MainWindow::handle_result()
{
    QString message;
    QString match = QString("Poland");
    int count = 0;

    if (worker->error_type == QNetworkReply::NoError)
    {
        message = "Success - Response: " + worker->response;    // komunikacja powiodła się

    }else{

        message = "Error: " + worker->error_str;    // wystąpił błąd
    }

    int firstCountryLetterIndex = 0;
    int firstRecordLetterIndex = 0;
    int lastRecordLetterIndex = 0;
    QString planeRecordData = "";
    QList <plane*> planesObjects;

    while ((firstCountryLetterIndex = message.indexOf(match, firstCountryLetterIndex)) != -1)
    {
        count++;
        qDebug() << "Found Poland tag at index position" << firstCountryLetterIndex;

        firstRecordLetterIndex = searchForBeginning(firstCountryLetterIndex, message);
        qDebug() << "Record begin: " << firstRecordLetterIndex;
        lastRecordLetterIndex = searchForEnd(firstCountryLetterIndex, message);
        qDebug() << "Record finish: " << lastRecordLetterIndex;
        planeRecordData = selectRecord(firstRecordLetterIndex, lastRecordLetterIndex, message);
        qDebug() << "Record: " << planeRecordData;

        planesObjects.push_back(parsingData(planeRecordData));

        ++firstCountryLetterIndex;

    }

    qDebug() << "Amount of elements in QList: " << planesObjects.size();

    for (int i = 0; i < planesObjects.size(); i++)
    {
        qDebug() << "Plane: " << i;
        qDebug() << "icao24: " << planesObjects[i]->getIcao24();
        qDebug() << "callsign: " << planesObjects[i]->getCallsign();
        qDebug() << "originCountry: " << planesObjects[i]->getOriginCountry();
        qDebug() << "timePosition: " << planesObjects[i]->getTimePosition();
        qDebug() << "timeVelocity: " << planesObjects[i]->getTimeVelocity();
        qDebug() << "longitude: " << planesObjects[i]->getLongitude();
        qDebug() << "latitude: " << planesObjects[i]->getLatitude();
        qDebug() << "altitude: " << planesObjects[i]->getAltitude();
        qDebug() << "onGround: " << planesObjects[i]->getOnGround();
        qDebug() << "velocity: " << planesObjects[i]->getVelocity();
        qDebug() << "heading: " << planesObjects[i]->getHeading();
        qDebug() << "verticalRate: " << planesObjects[i]->getVerticalRate();
        qDebug() << "sensors: " << planesObjects[i]->getSensors();
        qDebug() << "-------------------------------------------";
    }

    qDebug() << "Number of Poland tag at mesage" << count;          // początek informacji o samolocie zaczyna się 21 znaków wcześniej "[" do "]"

}

/*!
 * \brief MainWindow::parsingData(QString planeRecordData) - funkcja do parsowania danych tekstowych oraz tworzenia obiektów klasy plane
 *
 * - planeRecordData - dane typu QString z informacjami o samolocie
 *
 */

plane* MainWindow::parsingData(QString planeRecordData)
{
    QString planeData [18], tempData;
    int indexPlaneData = 0;

    for (int i = 0; i <= planeRecordData.size(); i++)
    {

        if ((planeRecordData[i] == ',') || (planeRecordData[i] == ']'))
        {
            planeData[indexPlaneData] = tempData;
//            qDebug() << tempData;
            tempData = "";
            indexPlaneData++;
        }

        if ((planeRecordData[i] != ' ') && (planeRecordData[i] != '"') && planeRecordData[i] != ',' && (planeRecordData[i] != '[') && (planeRecordData[i] != ']'))
        {
            tempData += planeRecordData[i];
        }
        //["4891a6","ENT582  ","Poland",1497533490,1497533490,7.2239,53.5819,10972.8,false,197.6,219.82,0,null,11193.78,null,false,false,0]
    }

    plane* Plane = new plane(planeData[0], planeData[1], planeData[2], planeData[3].toFloat(),
                    planeData[5].toFloat(),planeData[6].toFloat(),planeData[7].toFloat(),
                    planeData[8].toFloat(),toBoolean(planeData[9]),planeData[10].toFloat(),
                    planeData[11].toFloat(),planeData[12].toFloat(),planeData[13].toInt());

    return Plane;

}

/*!
 * \brief MainWindow::toBoolean(QString textToCheck) - funkcja do konwersji zmiennej tekstowej na boolean
 *
 * - textToCheck - dane typu QString do przekonwertowania
 *
 */

bool MainWindow::toBoolean(QString textToCheck)
{
    if ((textToCheck == "true") || (textToCheck == "TRUE") || (textToCheck == "1"))
    {
        return true;

    }else{

        return false;
    }
}


/*!
 * \brief MainWindow::takeScreen() - funkcja szukająca poczatku rekordu
 */

int MainWindow::searchForBeginning(int firstCountryLetterIndex, QString message)
{
    int tempLetterIndex = firstCountryLetterIndex;

    do
    {
        tempLetterIndex--;

    }while(message[tempLetterIndex] != '[');

    return tempLetterIndex;
}

/*!
 * \brief MainWindow::searchForEnd() - funkcja szukająca końca rekordu
 */

int MainWindow::searchForEnd(int firstCountryLetterIndex, QString message)
{
    int tempLetterIndex = firstCountryLetterIndex;

    do
    {
        tempLetterIndex++;

    }while(message[tempLetterIndex] != ']');

    return tempLetterIndex;
}

/*!
 * \brief MainWindow::selectRecord() - funkcja zwracająca rekord
 */

QString MainWindow::selectRecord(int firstRecordLetterIndex, int lastRecordLetterIndex, QString message)
{
    QString recordBuffer = "";

    for(int i = firstRecordLetterIndex; i <= lastRecordLetterIndex; i++)
    {
        recordBuffer += message[i];
    }

    return recordBuffer;
}



/*!
 * \brief MainWindow::takeScreen() - funkcja wykonująca zrzut całego okna aplikcji
 */

void MainWindow::takeScreen()
{
    image = QPixmap::grabWidget(this);                                        // sposób nr1 - tylko widget(nie widzi VTKWidget ;/ )
    //image = QPixmap::grabWindow(QApplication::desktop()->winId())             // sposób nr2 - cały pulpit
    //image = QPixmap::grabWindow(QApplication::desktop()->winId(),QMainWindow::x(),QMainWindow::y(),QMainWindow::width(),QMainWindow::height());  // sposób nr.3 - tylko okno

    saveScreen();
}

/*!
 * \brief MainWindow::saveScreen() - funkcja zapisuje wykonany zrzut ekranu do lokalizacji wybranej przez
 * użytkownika.
 */

void MainWindow::saveScreen()
{
    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                    .arg(format.toUpper())
                                                    .arg(format));
    if (!fileName.isEmpty())
        image.save(fileName, format.toLatin1().constData());

}

/*!
 * \brief MainWindow::aboutApp() - funkcja wyświetlająca okno "O aplikacji"
 */

void MainWindow::aboutApp()
{
    QMessageBox mssgbox;
    QString info;
    info = QString("<b>Nasz wspanialy radiator serwerowy :D</b><br /><br />") +
           //QString("<p><img src=\":/Images/Images/logo_ver2.png\" alt=\"logo\"></p>")+
           QString("Program <em><b>\"RADIATOR\"</b></em>   jest efektem pracy przy projekcie: \"Radiator Serwerowy wyswietlajacy dynamicznie inforamcje\" ") +
           QString("zmodyfikowany o mozliwosc dokonywania przekrojow. Stanowi on projekt zaliczeniowym autorstwa studentow: <br />")+
           QString("Michala Kluski  i Macieja Kucharskiego <br>") +
           QString("realizowanego w ramach przedmiotu \"Otwarte oprogramowanie w systemach wbudowanych\"<br/>AGH Czerwiec A.D.2017<br />")+
           QString("<hr><br>Osiagniete cele:<br /><ul>") +
           QString("<li>Wyswietla inforamcje</li>") +
           QString("<li>Pieknie dziala \\(^.^)/ .</li></ul>");

    mssgbox.information(this,"Informacje o programie",info);
//tytułem projektu, krótkim celem i założeniami projektu, danymi autora oraz nazwą przedmiotu, rok i miesiąc wykonania

}
