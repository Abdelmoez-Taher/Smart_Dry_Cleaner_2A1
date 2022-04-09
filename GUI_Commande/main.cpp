#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include <QMessageBox>
//#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createConnect();
    MainWindow w;
    QObject::connect(&a ,SIGNAL(focusChanged(QWidget *, QWidget *)), &w, SLOT(focusChanged(QWidget *, QWidget *)));

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),  //changé de "critical" à "information" pour indiquer que le message constitue une information ordinaire et non pas un problème
                    QObject::tr("Connexion réussie.\n"
                                "Appuyez sur Ok pour quitter."), QMessageBox::Ok);

}
    //qDebug() <<"Connexion réussie";
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Connexion échouée.\n"
                                "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);
    //qDebug() <<""erreur de connexion";

    return a.exec();
}
