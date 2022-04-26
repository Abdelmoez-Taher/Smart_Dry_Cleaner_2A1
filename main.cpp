#include "form.h"
#include"connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        connection c;
        bool test=c.createconnection();
        Form w;
        if(test)
        {
            w.show();
            QMessageBox::information(nullptr,QObject::tr("database is open"),
            QObject::tr("Welcome to DRY CLEANER.\n"
                        "Click cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                                  QObject::tr("connection failed.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);

    return a.exec();
}
