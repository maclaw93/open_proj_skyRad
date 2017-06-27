#include "mainwindow.h"

/*!
 *  \brief MainWindow::MainWindow - konstruktor klasy. Wywołuje tworzenie oraz budowanie wygladu okna glównego programu
 *         oraz przygotowanie powiązań interakcji pomiędzy elementami GUI.
 *  \param parent - wskaznik na obiekt nadrzędny.
 *
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    worker = new HttpRequestWorker(this);
    this->setGeometry(0,0,600,400);
    isFirstTime = true;

    //glowny panel GUI
    _mainWidget = new QWidget(this);
    _mainLayout = new QGridLayout(this);

    //elementy na glownym panelu
    _rightPart = new QGroupBox(this);
    _rightPartLayout = new QVBoxLayout;
    _tabele = new QTableView(this);

    //Timerowe rzeczy
    _timerGroup = new QGroupBox(_rightPart);
    _displTimeGroup = new QGroupBox(_timerGroup);
    _timeDispLayout = new QHBoxLayout;
    _timeInd = new QLabel;
    _timeText = new QLabel;
    _timeText2 = new QLabel;
    _timeText3 = new QLabel;
    _timerInd = new QLabel;
    _timeSlider = new QSlider;
    _acceptTimeButton = new QPushButton("START TIMER!!!");

    _timer = new QTimer;
    _cutdownTimer = new CutdownTimer(this,0,true);

    //wnętrze Gui od Timera
    //pierwsza linia
    _timeText->setText("Wybierz czas odswierzania w sek");
    //druga linia
    _timeSlider->setOrientation(Qt::Horizontal);
    _timeSlider->setRange(5,60);
    _timeSlider->setSingleStep(10);
    _timeSlider->setSliderPosition(10);
    //trzecia linia
    _timeInd->setNum(10);
    _timeText2->setText("Interwal odswierzania [sek]: ");
    _timeDispLayout->addWidget(_timeText2);
    _timeDispLayout->addWidget(_timeInd);
    _displTimeGroup->setLayout(_timeDispLayout);
    _displTimeGroup->setStyleSheet("border:0; margin: 0px 0px 0px;");
    //piąta linia
    _timeText3->setText("Licznik Timera [sek]:");
    _timerInd->setNum(0);
    _timerInd->setAlignment(Qt::AlignHCenter);

    //ulorzenie rzeczy od timera
    _timerSetLayout = new QVBoxLayout;
    _timerSetLayout->setAlignment(Qt::AlignHCenter);
    _timerSetLayout->addWidget(_timeText);
    _timerSetLayout->addWidget(_timeSlider);
    _timerSetLayout->addWidget(_displTimeGroup);
    _timerSetLayout->addWidget(_acceptTimeButton);
    _timerSetLayout->addWidget(_timeText3);
    _timerSetLayout->addWidget(_timerInd);
    _timerSetLayout->setSizeConstraint(QLayout::SetFixedSize);

    //ulożenie całego centaralnego GUI
    _timerGroup->setLayout(_timerSetLayout);
    _timerGroup->setTitle("Timer");
    _timerGroup->setStyleSheet("QGroupBox { border: 1px solid grey; border-radius: 9px; margin-top: 0.5em;} QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 0px 0 0px;}");
    _rightPartLayout->addWidget(_timerGroup);
    _rightPartLayout->setSizeConstraint(QLayout::SetFixedSize);  //grupa pozostaje tej samej wielkości
    _rightPart->setLayout(_rightPartLayout);
    _rightPart->setStyleSheet("margin: 0px 0px 0px;");
    _mainLayout->addWidget(_tabele,0,0,4,1); //tabela w komorce (0,0), ma sie rozciagac do IV rzedu i I kolumny
    _mainLayout->addWidget(_rightPart,0,1); //"lewa część" ma być ulokowana w komórce (0,1)
    _mainWidget->setLayout(_mainLayout);
    this->setCentralWidget(_mainWidget);
    this->setWindowTitle("Nowe GUI projektu");

    //belka menu
    _menuBar = new QMenuBar;
    _mainManu = new QMenu;
    _helpManu = new QMenu;
    //stoworzenie opcji z belki menu
    actionUpdate =_mainManu->addAction("Aktualizuj");
    actionUpdate->setToolTip("Pobieranie danych i ich parsowanie");
    actionUpdate->setShortcut(QKeySequence(tr("Ctrl+A")));
    actionSaveWindow = _mainManu->addAction("Zapisz zrzut ekranu");
    actionMinimized = _mainManu->addAction("Minimalizuj");
    actionMinimized->setShortcut(QKeySequence("Ctrl+M"));
    actionExite = _mainManu->addAction("Wyjscie");
    actionExite->setShortcut(QKeySequence("Alt+Esc"));
    actionAboutApp = _helpManu->addAction("O programie");
    _mainManu->setTitle("Pilk");
    _helpManu->setTitle("Pomoc");
    _menuBar->addMenu(_mainManu);
    _menuBar->addMenu(_helpManu);
    this->setMenuBar(_menuBar);

    //wyzbycie sie belki tytulowej okienka
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setConnections();

    //przygotowanie tabeli danych
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

    this->_tabele->setModel(model);
    _tabele->setEditTriggers(QAbstractItemView::NoEditTriggers); //zabezpieczenie nie edytowalnosci tabelki
}

/*!
 * \brief MainWindow::~MainWindow() - destruktory
 */

MainWindow::~MainWindow()
{
    delete worker;
    delete model;
    this->_timer->stop();
    this->_cutdownTimer->elapsStop();
    delete _timer;
    delete _cutdownTimer;
    this->destroy();
}

/*!
 * \brief MainWindow::setConnections() - funkcja zawierająca sygnały i sloty.
 */

void MainWindow::setConnections()
{
    connect(this->actionUpdate, SIGNAL(triggered()),                // połączenie przycisku z menu z metodą aktualizuj dane
            this, SLOT(updateData()));
    connect(this->actionExite, SIGNAL(triggered()),                  // połączenie przycisku z menu z metodą zamykajacą aplikację
            this, SLOT(close()));
    connect(this->actionSaveWindow, SIGNAL(triggered()),          // połączenie przycisku z menu z metodą wykonującą zrzut ekranu
            this, SLOT(takeScreen()));
    connect(this->actionAboutApp, SIGNAL(triggered()),            // połączenie przycisku z menu z metodą wyświetlającą informację o aplikacji
            this, SLOT(aboutApp()));
    connect(this->actionMinimized, SIGNAL(triggered()),
            this, SLOT(showMinimized()));
    connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)),  // połaczenie worker-a z metodą odbierajaca dane
            this, SLOT(handle_result()));
    connect(this->_timeSlider, SIGNAL(valueChanged(int)),
            this->_timeInd, SLOT(setNum(int)));
    connect(this->_timer, SIGNAL(timeout()),
            this, SLOT(updateTrigged()));
    connect(this, SIGNAL(go()),
            this->_timer, SLOT(start()));
    connect(this, SIGNAL(go()),
            this->_cutdownTimer, SLOT(elapsStrat()));
    connect(this->_acceptTimeButton, SIGNAL(clicked()),
            this, SLOT(prepareTimer()));
    connect(this->_cutdownTimer, SIGNAL(timeout()),
            this, SLOT(displRemaningTime()));
}

/*!
 * \brief MainWindow::displRemaningTime() - funkcja zwracająca pozostały czas do następnego odświeżenia.
 */

void MainWindow::displRemaningTime()
{
    int d = this->_cutdownTimer->getRameining();
    this->_timerInd->setNum(d);
}

/*!
 * \brief MainWindow::updateTrigged() - funkcja odświeżająca dane po odliczeniu czasu przez Timer.
 */

void MainWindow::updateTrigged()
{
    qDebug() << "Timer is up, update trigged";
    this->updateData();
}

/*!
 * \brief MainWindow::prepareTimer() - funkcja przygotowywująca i wyzwalająca timery.
 */
void MainWindow::prepareTimer()
{
    this->_timer->setInterval((this->_timeSlider->value())*1000);
    this->_cutdownTimer->setTimeToElaps(this->_timeSlider->value());
    if(isFirstTime)
    {
        this->updateData();
    }
    emit go();
}

/*!
 * \brief MainWindow::updateData() - funkcja wykonująca zapytanie GET.
 */

void MainWindow::updateData()
{
    this->isFirstTime = false;
    QString url_str = "https://opensky-network.org/api/states/all";

    HttpRequestInput input(url_str, "GET");
    worker->execute(&input);
}

/*!
 * \brief MainWindow::handle_result() - funkcja wyłapująca odpowiedź, wyszukuje informacje o Polskich samolotach,
 * przekazuje je do przetworzenia oraz odpowiada za uzupełenie tabeli, na podstawie otrzymanych wyników.
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

        firstRecordLetterIndex = searchForBeginning(firstCountryLetterIndex, message);
        lastRecordLetterIndex = searchForEnd(firstCountryLetterIndex, message);
        planeRecordData = selectRecord(firstRecordLetterIndex, lastRecordLetterIndex, message);

        planesObjects.push_back(parsingData(planeRecordData));

        ++firstCountryLetterIndex;

    }


    for (int i = 0; i < planesObjects.size(); i++)
    {
        QStandardItem *row0 = new QStandardItem(planesObjects[i]->getIcao24());
        model->setItem(i, 0, row0);

        QStandardItem *row1 = new QStandardItem(planesObjects[i]->getCallsign());
        model->setItem(i, 1, row1);

        QStandardItem *row2 = new QStandardItem(planesObjects[i]->getOriginCountry());
        model->setItem(i, 2, row2);

        QStandardItem *row3 = new QStandardItem(QString::number(planesObjects[i]->getTimePosition()));
        model->setItem(i, 3, row3);

        QStandardItem *row4 = new QStandardItem(QString::number(planesObjects[i]->getTimeVelocity()));
        model->setItem(i, 4, row4);

        QStandardItem *row5 = new QStandardItem(QString::number(planesObjects[i]->getLongitude()));
        model->setItem(i, 5, row5);

        QStandardItem *row6 = new QStandardItem(QString::number(planesObjects[i]->getLatitude()));
        model->setItem(i, 6, row6);

        QStandardItem *row7 = new QStandardItem(QString::number(planesObjects[i]->getAltitude()));
        model->setItem(i, 7, row7);

        QStandardItem *row8 = new QStandardItem(QString::number(planesObjects[i]->getOnGround()));
        model->setItem(i, 8, row8);

        QStandardItem *row9 = new QStandardItem(QString::number(planesObjects[i]->getVelocity()));
        model->setItem(i, 9, row9);

        QStandardItem *row10 = new QStandardItem(QString::number(planesObjects[i]->getHeading()));
        model->setItem(i, 10, row10);

        QStandardItem *row11 = new QStandardItem(QString::number(planesObjects[i]->getVerticalRate()));
        model->setItem(i, 11, row11);

        QStandardItem *row12 = new QStandardItem(QString::number(planesObjects[i]->getSensors()));
        model->setItem(i, 12, row12);

    }
    this->_tabele->setModel(model);

    qDebug() << "Number of Poland tag at mesage" << count;

}

/*!
 * \brief MainWindow::parsingData(QString planeRecordData) - funkcja do parsowania danych tekstowych oraz tworzenia obiektów klasy plane.
 *
 * - planeRecordData - dane typu QString z informacjami o samolocie.
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
            tempData = "";
            indexPlaneData++;
        }

        if ((planeRecordData[i] != ' ') && (planeRecordData[i] != '"') && planeRecordData[i] != ',' && (planeRecordData[i] != '[') && (planeRecordData[i] != ']'))
        {
            tempData += planeRecordData[i];
        }
    }

    plane* Plane = new plane(planeData[0], planeData[1], planeData[2], planeData[3].toFloat(),
            planeData[5].toFloat(),planeData[6].toFloat(),planeData[7].toFloat(),
            planeData[8].toFloat(),toBoolean(planeData[9]),planeData[10].toFloat(),
            planeData[11].toFloat(),planeData[12].toFloat(),planeData[13].toInt());

    return Plane;

}

/*!
 * \brief MainWindow::toBoolean(QString textToCheck) - funkcja do konwersji zmiennej tekstowej na boolean.
 *
 * - textToCheck - dane typu QString do przekonwertowania.
 *
 */

bool MainWindow::toBoolean(QString textToCheck)
{
    if ((textToCheck == "true") || (textToCheck == "TRUE") || (textToCheck == "1"))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*!
 * \brief MainWindow::searchForBeginning(int firstCountryLetterIndex, QString message) - funkcja zwracjąca indeks początku rekordu w otrzymanym ciagu do analizy.
 *
 * - firstCountryLetterIndex - zmienna typu integer przechowuje indeks pierwszej litery szukanej frazy ( w naszym przypadku "P" - Poland).
 * - message - zmienna typu QString zawiera odebrane dane z serwera.
 *
 */

int MainWindow::searchForBeginning(int firstCountryLetterIndex, QString message)
{
    int tempLetterIndex = firstCountryLetterIndex;

    do
    {
        tempLetterIndex--;
    }
    while(message[tempLetterIndex] != '[');

    return tempLetterIndex;
}

/*!
 * \brief MainWindow::searchForEnd(int firstCountryLetterIndex, QString message) - funkcja zwracjąca indeks końca rekordu w otrzymanym ciagu do analizy.
 *
 * - firstCountryLetterIndex - zmienna typu integer przechowuje indeks pierwszej litery szukanej frazy ( w naszym przypadku "P" - Poland).
 * - message - zmienna typu QString zawiera odebrane dane z serwera.
 *
 */

int MainWindow::searchForEnd(int firstCountryLetterIndex, QString message)
{
    int tempLetterIndex = firstCountryLetterIndex;

    do
    {
        tempLetterIndex++;
    }
    while(message[tempLetterIndex] != ']');

    return tempLetterIndex;
}

/*!
 * \brief MainWindow::selectRecord(int firstRecordLetterIndex, int lastRecordLetterIndex, QString message) - funkcja zwracająca rekord z danymi jednego samolotu.
 *
 * - firstRecordLetterIndex - zmienna typu integer przechowuje indeks pierwszej litery rekordu infromacji o wybranym samolocie.
 * - lastRecordLetterIndex - zmienna typu integer przechowuje indeks ostatniej litery rekordu infromacji o wybranym samolocie.
 * - message - zmienna typu QString zawiera odebrane dane z serwera.
 *
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
 * \brief MainWindow::takeScreen() - funkcja wykonująca zrzut całego okna aplikcji.
 */

void MainWindow::takeScreen()
{
    image = QPixmap::grabWidget(this);
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
            QString("Program <em><b>\"skyRad\"</b></em>   jest efektem pracy przy projekcie: \"Radiator Serwerowy wyswietlajacy dynamicznie inforamcje\" ") +
            QString("Stanowi on projekt zaliczeniowym autorstwa studentow: <br />")+
            QString("Michala Kluski  i Macieja Kucharskiego <br>") +
            QString("realizowanego w ramach przedmiotu \"Otwarte oprogramowanie w systemach wbudowanych\"<br/>AGH Czerwiec A.D.2017<br />")+
            QString("<hr><br>Osiagniete cele:<br /><ul>") +
            QString("<li>Pobiera informacje o polskich samolotach w powietrzu poprzez zapytanie REST</li>") +
            QString("<li>Wyswietla inforamcje w formie tabelki</li>") +
            QString("<li>Automatycznie odswierza dane co ustalany przez urzytkownika czas</li>") +
            QString("<li>Pieknie dziala \\(^.^)/ .</li></ul>");

    mssgbox.information(this,"Informacje o programie",info);
}
