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

private:
    Ui::AddUser *m_ui;
};

#endif // ADDUSER_H
