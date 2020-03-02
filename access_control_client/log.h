#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class Log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = nullptr);
    ~Log();
    void load(QStringList, QStringList, QStringList);

private slots:

private:
    Ui::Log *m_ui;
};

#endif // LOG_H
