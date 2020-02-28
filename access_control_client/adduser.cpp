#include "adduser.h"
#include "ui_adduser.h"
#include <QDialogButtonBox>
#include <QPushButton>

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddUser)
{
    m_ui->setupUi(this);
    setFixedSize(size());
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(m_ui->password_re, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));

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

void AddUser::checkPassword(const QString& passwordRe)
{

    if(m_ui->password->text() == passwordRe)
    {
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        m_ui->check->setText("");
    }
    else
    {
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        m_ui->check->setText("Passwords don't match");
    }//end if

}
