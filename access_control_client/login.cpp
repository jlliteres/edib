#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Login)
{
    m_ui->setupUi(this);
    this->setWindowTitle("Login");
}

Login::~Login()
{
    delete m_ui;
}

void Login::on_buttonBox_accepted()
{

}
