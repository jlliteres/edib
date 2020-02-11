#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnClose_clicked();
    void on_btnSend_clicked();

    void on_btnOpen_clicked();

private:
    Ui::MainWindow *m_ui;
    ix::WebSocket m_webSocket;
    QString serverUrl{"ws://localhost:9900/"};

    int clientID{1};

    void add_log(QString item);
    void init_server(QString url);

};

#endif // MAINWINDOW_H
