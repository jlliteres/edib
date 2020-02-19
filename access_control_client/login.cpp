#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Login)
{
    m_ui->setupUi(this);
    this->setWindowTitle("Admin Login");
}

Login::~Login()
{
    delete m_ui;
}

std::string Login::user()
{
    return m_ui->user->text().toStdString();
}

std::string Login::password()
{
    return m_ui->password->text().toStdString();
}
