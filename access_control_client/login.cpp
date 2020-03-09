#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Login)
{
    m_ui->setupUi(this);
    this->setWindowTitle(tr("Login"));
    setFixedSize(size());
    m_ui->warning->setHidden(true);
}

Login::~Login()
{
    delete m_ui;
}

void Login::setUser(QString user)
{
    m_ui->user->setText(user);
    m_ui->user->setReadOnly(true);
}

std::string Login::user()
{
    return m_ui->user->text().toStdString();
}

std::string Login::password()
{
    return m_ui->password->text().toStdString();
}

void Login::hidePassword(bool state)
{
    m_ui->lblPassword->setHidden(state);
    m_ui->password->setHidden(state);
    m_ui->warning->setHidden(!state);
}
