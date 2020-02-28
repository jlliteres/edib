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

    void lock();
    void unlock();
    void load();

    void logUser(int);
    void fillTable(QStringList, QStringList, int);
    void warningMsg(QString);

    bool exists(const JSON&, const std::string&);

public slots:
    void loginUser(const QString&, int);
    void filter(const QString&, int);

private slots:
    void on_btnClose_clicked();
    void on_btnOpen_clicked();

    void on_btnLock_clicked();

    void on_action_Exit_triggered();

    void on_filterOut_textChanged(const QString &arg1);
    void on_filterIn_textChanged(const QString &arg1);

    void on_btnEnter_clicked();
    void on_btnExit_clicked();

    void on_btnAdd_clicked();

private:
    Ui::MainWindow *m_ui;
    ix::WebSocket m_webSocket;
    QString m_serverUrl{""};
    int m_clientID{1};

    bool m_isLocked{true};
    void init_server(QString url);

};

#endif // MAINWINDOW_H
