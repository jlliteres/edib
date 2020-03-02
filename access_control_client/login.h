/**
    @file login.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Login or delete user dialog.
    @brief QDialog class with 'user' and 'password' fields.
  */
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
    /**
     * @brief Login Default constructor.
     * @param parent Object parent.
     */
    explicit Login(QWidget *parent = nullptr);
    /**
     * @brief ~Login Default destructor.
     */
    ~Login();
    /**
     * @brief setUser Sets the user name, usable when login in or deleting an user.
     * @param name User name.
     */
    void setUser(QString name);
    /**
     * @brief user Returns the value of the user input field
     * @return QLineEdit.text()
     */
    std::string user();
    /**
     * @brief password Returns the value of the password input field
     * @return QLineEdit.text()
     */
    std::string password();
    /**
     * @brief hidePassword Hides the password field and label, usable when deleting an user.
     * @param state Boolean switcher.
     */
    void hidePassword(bool state);
private slots:

private:
    Ui::Login *m_ui;
};

#endif // LOGIN_H
