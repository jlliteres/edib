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
    m_ui->changePassword->hide();
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

void AddUser::setUser(QString user)
{
    ///Set user field.
    m_ui->user->setText(user);
}

void AddUser::showChangePassword(bool state)
{
   ///Show change password checkbox when modifying an user.
   m_ui->changePassword->setVisible(state);
   m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
   m_ui->password->setEnabled(!state);
   m_ui->password_re->setEnabled(!state);
}

void AddUser::checkPassword(const QString& passwordRe)
{
    ///Check if both passwords match.
    if(m_ui->changePassword->isHidden() || m_ui->changePassword->isChecked())
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
    }//end if
}

void AddUser::on_changePassword_toggled(bool checked)
{
    ///Deactivate OK button for passwords match comprobation.
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!checked);
    m_ui->password->setEnabled(checked);
    m_ui->password_re->setEnabled(checked);
}
