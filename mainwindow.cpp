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
 * \brief MainWindow::~MainWindow() - funkcja zawierająca destruktory
 */

Main+Window::~MainWindow()
{
    delete ui;
    delete wor

            ker;
}

/*!
 * \brief MainWindow::setConnections() - funkcja zawierająca sygnały i sloty
 */

void MainWindow::setConnections()
{
    connect(ui->actionUpdate, SIGNAL(triggered()),                      // połączenie przycisku z menu z metodą aktualizuj dane
            this, SLOT(updateData()));
    connect(ui->actionExit, SIGNAL(triggered()),                        // połączenie przycisku z menu z metodą zamykajacą aplikację
 dfsgfsbd           this, SLOT(close()));
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

//        for(int i=0; i<=5; i++)
//        {
//            qDebug() << message[firstCountryLetterIndex + i];
//        }

        ++firstCountryLetterIndex;

    }

    qDebug() << "Number of Poland tag at mesage" << count;          // początek informajci o samolocie zaczyna się 21 znaków wcześniej "[" do "]"
    //QMessageBox::information(this, "", msg);
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
