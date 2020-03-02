/**
    @file log.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Class that manages showing access control info.
    @brief QDialog class with QTableWidget for the users log table.
  */
#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class Log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Log Default constructor.
     * @param parent Parent object.
     */
    explicit Log(QWidget *parent = nullptr);
    /**
     * @brief ~Log Default destructor.
     */
    ~Log();
    /**
     * @brief load Function that fills the QTableWidget with the given info.
     * @param listName QStringList of all the users names in the log.
     * @param listEnter QStringList of all the enter_time of the users.
     * @param listExit QStringList of all the exit_time of the users.
     */
    void load(QStringList listName, QStringList listEnter, QStringList listExit);

private slots:

private:
    Ui::Log *m_ui;
};

#endif // LOG_H
