#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    std::string user();
    std::string password();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Login *m_ui;
};

#endif // LOGIN_H
