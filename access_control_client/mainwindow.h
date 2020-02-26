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
    void lock();
    void unlock();

    void enter();
    void exit();

    ~MainWindow();
    void fillTable(QStringList, QStringList);
    void warningMsg(QString);

private slots:
    void on_btnClose_clicked();
    void on_btnSend_clicked();
    bool exists(const JSON&, const std::string&);
    void on_btnOpen_clicked();

    void on_btnLock_clicked();

    void on_action_Exit_triggered();

    void on_filterOut_textChanged(const QString &arg1);
    void on_filterIn_textChanged(const QString &arg1);

    void on_btnEnter_clicked();

    void on_btnExit_clicked();

private:
    Ui::MainWindow *m_ui;
    ix::WebSocket m_webSocket;
    QString m_serverUrl{""};
    int m_clientID{1};
    bool m_isLocked{true};
    void init_server(QString url);

};

#endif // MAINWINDOW_H
