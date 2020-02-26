#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void setUser(QString);
    std::string user();
    std::string password();

private slots:

private:
    Ui::Login *m_ui;
};

#endif // LOGIN_H
