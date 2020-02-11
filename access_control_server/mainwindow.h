#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Server m_server;

private:
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_H
