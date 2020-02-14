#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"

using JSON = nlohmann::json;

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
    bool exists(const JSON&, const std::string&);
    void on_btnOpen_clicked();

private:
    Ui::MainWindow *m_ui;
    ix::WebSocket m_webSocket;
    QString m_serverUrl{""};

    int clientID{1};

    void add_log(QString item);
    void init_server(QString url);

};

#endif // MAINWINDOW_H
