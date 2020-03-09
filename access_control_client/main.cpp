#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;

    QStringList languages;
    languages << "English" << "Español";

    QInputDialog input;

    QString result = input.getItem(NULL, "Select Language", "Language", languages);

    if(result != "English")
    {
        t.load(":/es_ES.qm");
        a.installTranslator(&t);
    }//end if

    MainWindow w;
    w.show();

    return a.exec();


}
