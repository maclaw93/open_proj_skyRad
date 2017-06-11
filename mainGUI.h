#ifndef MAINGUI_H
#define MAINGUI_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QToolBar>
#include <QStatusBar>

#include <QtNetwork/QNetworkReply>
#include <QMessageBox>

#include <QDir>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPixmap>
#include <QTableView>
#include "httprequestworker.h"
#include <QDebug>

class MainGUI : public QMainWindow
{
    Q_OBJECT

protected:
    void setConnections();                      ///< metoda do inicjalizacji połoczeń SIGNAL-SLOT

public:
    MainGUI(QWidget *parent = 0);
    ~MainGUI();

private:
    QPixmap image;                              ///<zmienna zapamiętująca obraz
    HttpRequestWorker *worker;

    //wskazniki od wytworzenia okienka
    QWidget* _mainWidget;
    QHBoxLayout* _mainLayout;
    QMenuBar* _menuBar;
    QMenu* _mainManu;
    QMenu* _helpManu;
    QToolBar* _mainToolBar;
    QStatusBar* _mainStatusBar;

    //elementy GUI
    QTableView* _tabela;

protected:
    QAction* actionUpdate;
    QAction* actionExite;
    QAction* actionSaveWindow;
    QAction* actionAboutApp;
    QAction* actionMinimized;
    QAction* actionAboutQt;


private slots:
    void updateData();
    void handle_result();
    void takeScreen();                          ///< metoda wykonywanie screenshot-a
    void saveScreen();                          ///< metoda do zapisywania screen-ów
    void aboutApp();                            ///< metoda do wyświetlania inforamcji o aplikacji

};

#endif // MAINGUI_H
