/**
    @file adduser.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Add or modify user dialog.
    @brief QDialog class with 'user', 'password' and 'confirm password' fields.
  */
#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief AddUser Default constructor
     * @param parent QWidget *parent object
     */
    explicit AddUser(QWidget *parent = nullptr);
    /**
     * @brief ~AddUser Default destructor
     */
    ~AddUser();
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
     * @brief setUser Sets the user name, usable when modifying an user.
     * @param user User name.
     */
    void setUser(QString user);
    /**
     * @brief showChangePassword Show or hide "Change password?" checkbox and disable or enable password fields.
     * @param state Boolean switch.
     */
    void showChangePassword(bool state);

public slots:
    /**
     * @brief checkPassword SLOT. Checks if both password fields are the same and enables "Ok" button if they are.
     * @param text Takes the 'confirm pasword' input field.
     */
    void checkPassword(const QString& text);

private slots:
    void on_changePassword_toggled(bool checked);

private:
    Ui::AddUser *m_ui;
};

#endif // ADDUSER_H
