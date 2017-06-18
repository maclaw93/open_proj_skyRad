#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    worker = new HttpRequestWorker(this);
    //this->setGeometry(0,0,600,400);

    //glowny panel GUI
    _mainWidget = new QWidget(this);
    _mainLayout = new QHBoxLayout(this);

    //elementy na glownym panelu
    _leftPart = new QGroupBox(this);
    _leftPartLayout = new QVBoxLayout;
    _tabela = new QTableView(this);
    //_tabela->setGeometry(0,0,800,400);

    //Timerowe rzeczy
    _timerGroup = new QGroupBox(_leftPart);
    _displTimeGroup = new QGroupBox(_timerGroup);
    _timeDispLayout = new QHBoxLayout;
    _timeInd = new QLabel;
    _timeText = new QLabel;
    _timeText2 = new QLabel;
    _timeText3 = new QLabel;
    _timerInd = new QLabel;
    _timer = new QTimer;
    _timeSlider = new QSlider;
    _acceptTimeButton = new QPushButton("START TIMER!!!");
    _acceptTimeButton->setDisabled(true);

    //wnętrze Gui od Timera
    //pierwsza linia
    _timeText->setText("Wybierz czas odswierzania w sek");
    _timeText->setFont(QFont("arial",10,2,true));
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
    _displTimeGroup->setFlat(true);
    //piąta linia
    _timeText3->setText("Licznik Timera [sek]:");
    _timerInd->setNum(0.0);

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

    ///ulorzenie calego centaralnego GUI
    _timerGroup->setLayout(_timerSetLayout);
    _timerGroup->setFlat(false);
    _timerGroup->setTitle("Timer");
    _timerGroup->setStyleSheet("QGroupBox { border: 1px solid grey; border-radius: 9px; margin-top: 0.5em;} QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 0px 0 0px;}");
    _leftPartLayout->addWidget(_timerGroup);
    _leftPartLayout->setSizeConstraint(QLayout::SetFixedSize);  //to powoduje ze zostaje tej samej wielkosci ta grupa
    //_leftPart->setFlat(true);
    _leftPart->setLayout(_leftPartLayout);
    _mainLayout->addWidget(_tabela);
    _mainLayout->addWidget(_leftPart);
    _mainWidget->setLayout(_mainLayout);
    this->setCentralWidget(_mainWidget);
    this->setWindowTitle("Nowe GUI projektu");

    //belka menu
    _menuBar = new QMenuBar;
    _mainManu = new QMenu;
    _helpManu = new QMenu;
    //stoworzenie opcji z belki menu
    actionUpdate =_mainManu->addAction("Aktualizuj");
    actionSaveWindow = _mainManu->addAction("Zapisz zrzut ekranu");
    actionMinimized = _mainManu->addAction("Minimalizuj");
    actionExite = _mainManu->addAction("Wyjscie");
    actionAboutApp = _helpManu->addAction("O programie");
    _mainManu->setTitle("Pilk");
    _helpManu->setTitle("Pomoc");
    _helpManu->setToolTip("Menu zawierajace informacie o projekcie i innych szczegolach technicznych");
    _menuBar->addMenu(_mainManu);
    _menuBar->addMenu(_helpManu);
    this->setMenuBar(_menuBar);

    setConnections();
}

MainWindow::~MainWindow()
{
    delete worker;
    this->destroy();
}

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
    //connect(this->actionAboutQt, SIGNAL(triggered()),             // połączenie przycisku z menu z metodą wyświetlajacą informacje o Qt
    //        qApp, SLOT(aboutQt()));
    connect(this->actionMinimized, SIGNAL(triggered()),
            this, SLOT(showMinimized()));
    connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)),
            this, SLOT(handle_result()));
    connect(this->_timeSlider, SIGNAL(valueChanged(int)),
            this->_timeInd, SLOT(setNum(int)));
    connect(this->_timeSlider, SIGNAL(sliderReleased()),
            this, SLOT(prepareTimer()));
}

void MainWindow::prepareTimer()
{
    int timerPeriod = this->_timeSlider->value();
    this->_timer->setInterval(timerPeriod*1000);
    qDebug() << "Timer set to " << timerPeriod;
    qDebug() << "Timer redy to go!!";
    this->_acceptTimeButton->setEnabled(true);
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
 *  - worker - wskaźnik na połączenie
 */

void MainWindow::handle_result() {
    QString msg;
    QString match = QString("Poland");
    int count = 0;

    if (worker->error_type == QNetworkReply::NoError) {
        // communication was successful
        msg = "Success - Response: " + worker->response;
    }
    else {
        // an error occurred
        msg = "Error: " + worker->error_str;
    }

    int j = 0;

    while ((j = msg.indexOf(match, j)) != -1)
    {
        count++;
        qDebug() << "Found Poland tag at index position" << j;

        for(int i=0;i<=5;i++)
        {
            qDebug() << msg[j+i];
        }
        ++j;

    }

    qDebug() << "Number of Poland tag at mesage" << count;          // początek informajci o samolocie zaczyna się 21 znaków wcześniej "[" do "]"
    //QMessageBox::information(this, "", msg);
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
            QString("Program <em><b>\"skyRad\"</b></em>   jest efektem pracy przy projekcie: \"Radiator Serwerowy wyswietlajacy dynamicznie inforamcje\" ") +
            QString("Stanowi on projekt zaliczeniowym autorstwa studentow: <br />")+
            QString("Michala Kluski  i Macieja Kucharskiego <br>") +
            QString("realizowanego w ramach przedmiotu \"Otwarte oprogramowanie w systemach wbudowanych\"<br/>AGH Czerwiec A.D.2017<br />")+
            QString("<hr><br>Osiagniete cele:<br /><ul>") +
            QString("<li>Pobiera informacje o polskich samolotach w powietrzu poprzez zapytanie REST</li>") +
            QString("<li>Wyswietla inforamcje w formie tabelki</li>") +
            QString("<li>Pieknie dziala \\(^.^)/ .</li></ul>");

    mssgbox.information(this,"Informacje o programie",info);
}
