#include "log.h"
#include "ui_log.h"
#include <QDebug>

Log::Log(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Log)
{

    m_ui->setupUi(this);
    setFixedSize(size());
    m_ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


Log::~Log()
{
    delete m_ui;
}

void Log::load(QStringList listName, QStringList listEnter, QStringList listExit)
{
    int row{0};
    int column{0};

    QTableWidget *table = m_ui->table;

    /// Restart table and set headers
    table->setRowCount(0);
    table->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("enter_time") << tr("exit_time"));

    for(QString user : listName)
    {
        qDebug () << user;
        QTableWidgetItem *name = new QTableWidgetItem(user);
        QTableWidgetItem *enter = new QTableWidgetItem(listEnter.value(listName.indexOf(user)));
        QTableWidgetItem *exit = new QTableWidgetItem(listExit.value(listName.indexOf(user)));

        table->insertRow(row);
        table->setItem(row, column, name);
        column++;
        table->setItem(row, column, enter);
        column++;
        table->setItem(row, column, exit);
        row++;
        column = 0;

        exit->setTextAlignment(Qt::AlignCenter);
        enter->setTextAlignment(Qt::AlignCenter);
        name->setTextAlignment(Qt::AlignCenter);
    }

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

