#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddUser)
{
    m_ui->setupUi(this);
    setFixedSize(size());
}

AddUser::~AddUser()
{
    delete m_ui;
}

std::string AddUser::user()
{
    return m_ui->user->text().toStdString();
}

std::string AddUser::password()
{
    return m_ui->password->text().toStdString();
}
