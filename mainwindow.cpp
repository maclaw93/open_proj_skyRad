#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    worker = new HttpRequestWorker(this);
    setConnections();

    model = new QStandardItemModel(1,1,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Icao24")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Callsign")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Origin Country")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Time Position")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Time Velocity")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Longitude")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Latitude")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Altitude")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("On Ground")));
    model->setHorizontalHeaderItem(9, new QStandardItem(QString("Velocity")));
    model->setHorizontalHeaderItem(10, new QStandardItem(QString("Heading")));
    model->setHorizontalHeaderItem(11, new QStandardItem(QString("Vertical Rate")));
    model->setHorizontalHeaderItem(12, new QStandardItem(QString("Sensors")));

    ui->tableView->setModel(model);
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
        QStandardItem *row0 = new QStandardItem(planesObjects[i]->getIcao24());          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 0, row0);

        QStandardItem *row1 = new QStandardItem(planesObjects[i]->getCallsign());          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 1, row1);

        QStandardItem *row2 = new QStandardItem(planesObjects[i]->getOriginCountry());          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 2, row2);

        QStandardItem *row3 = new QStandardItem(QString::number(planesObjects[i]->getTimePosition()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 3, row3);

        QStandardItem *row4 = new QStandardItem(QString::number(planesObjects[i]->getTimeVelocity()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 4, row4);

        QStandardItem *row5 = new QStandardItem(QString::number(planesObjects[i]->getLongitude()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 5, row5);

        QStandardItem *row6 = new QStandardItem(QString::number(planesObjects[i]->getLatitude()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 6, row6);

        QStandardItem *row7 = new QStandardItem(QString::number(planesObjects[i]->getAltitude()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 7, row7);

        QStandardItem *row8 = new QStandardItem(QString::number(planesObjects[i]->getOnGround()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 8, row8);

        QStandardItem *row9 = new QStandardItem(QString::number(planesObjects[i]->getVelocity()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 9, row9);

        QStandardItem *row10 = new QStandardItem(QString::number(planesObjects[i]->getHeading()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 10, row10);

        QStandardItem *row11 = new QStandardItem(QString::number(planesObjects[i]->getVerticalRate()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 11, row11);

        QStandardItem *row12 = new QStandardItem(QString::number(planesObjects[i]->getSensors()));          //GDZIE ZABIJAĆ TE OBIEKTY????
        model->setItem(i, 12, row12);

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
    ui->tableView->setModel(model);

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
