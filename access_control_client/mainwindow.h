/**
    @file adduser.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title MainWindow UI.
    @brief UI for visual display of client info.
  */
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
    /**
     * @brief MainWindow Default constructor.
     * @param parent Object parent.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
     * @brief ~MainWindow Default destructor.
     */
    ~MainWindow();
    /**
     * @brief lock Visual changes when need to lock admin options.
     */
    void lock();
    /**
     * @brief unlock Visual changes when need to unlock admin options.
     */
    void unlock();
    /**
     * @brief load Prepares and sends JSON to server to load table info.
     */
    void load();
    /**
     * @brief logUser Moves one user from table to table.
     * @param switcher Determines which table is the start table and which the end table.
     * @code
        table = (switcher == 0)? m_ui->tblOUT:m_ui->tblIN;
     * @endcode
     */
    void logUser(int switcher);
    /**
     * @brief fillTable Shows the loaded info in the table.
     * @param listID List of the users ID number.
     * @param listName List of the users names.
     * @param switcher Determines which table to fill.
     * @code
        table = (switcher == 0)? m_ui->tblOUT:m_ui->tblIN;
     * @endcode
     */
    void fillTable(QStringList listID, QStringList listName, int switcher);
    /**
     * @brief fillLog Function that fills the log QTableWidget with the given info.
     * @param listName QStringList of all the users names in the log.
     * @param listEnter QStringList of all the enter_time of the users.
     * @param listExit QStringList of all the exit_time of the users.
     */
    void fillLog(QStringList listName, QStringList listEnter, QStringList listExit);
    /**
     * @brief exists Determines if a given JSON contains a given key.
     * @param json JSON given.
     * @param key String key given.
     * @return Returns a boolean if json contains key.
     */
    bool exists(const JSON& json, const std::string& key);

public slots:
    /**
     * @brief loginUser Shows a QDialog for user login credentials.
     * @param name User name to be set on the dialog.
     * @param switcher Determines which table is selected.
     * @code
        table = (switcher == 0)? m_ui->tblOUT:m_ui->tblIN;
     * @endcode
     */
    void loginUser(const QString& name, int switcher);
    /**
     * @brief filter Filters the table results.
     * @param text Filter text.
     * @param switcher Determines which table is selected.
     * @code
        table = (switcher == 0)? m_ui->tblOUT:m_ui->tblIN;
     * @endcode
     */
    void filter(const QString& text, int switcher);

signals:
    void signalLog(QStringList, QStringList, QStringList);

private slots:
    void on_btnLock_clicked();

    void on_action_Exit_triggered();
    void on_filterOut_textChanged(const QString &arg1);
    void on_filterIn_textChanged(const QString &arg1);

    void on_btnEnter_clicked();
    void on_btnExit_clicked();

    void on_btnAdd_clicked();
    void on_btnModify_clicked();

    void on_action_Info_triggered();

    void on_btnDelete_clicked();

private:
    Ui::MainWindow *m_ui;
    ix::WebSocket m_webSocket;
    QString m_serverUrl{""};
    int m_clientID{1};

    bool m_isLocked{true};
    void init_server(QString url);

};

#endif // MAINWINDOW_H
