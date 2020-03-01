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
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();
    std::string user();
    std::string password();
    void setUser(QString);
    void showChangePassword(bool);

public slots:
    void checkPassword(const QString&);

private slots:
    void on_changePassword_toggled(bool checked);

private:
    Ui::AddUser *m_ui;
};

#endif // ADDUSER_H
