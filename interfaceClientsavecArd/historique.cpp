#include "historique.h"
#include<QMessageBox>
#include <QDateTime>

Historique::Historique()
{
tmp="";
}
void Historique::save(QString CIN,QString NOM,QString NUM_TELEPHONE)
{    QFile file ("C:/Users/LENOVO/Documents/interfaceClientsansArd/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << CIN+"\n"+NOM << "\n" +NUM_TELEPHONE<< "\n un nouveau client a etat ajouter le " +sDate << "\n";


}
QString Historique::load()
{   tmp="";
    QFile file("C:/Users/LENOVO/Documents/interfaceClientsansArd/Historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {


         QString myString = in.readLine();
         tmp+=myString+"\n";


   }
   return tmp;
}
void Historique::save1(QString CIN,QString NOM,QString NUM_TELEPHONE,QString EMAIL)
{    QFile file ("C:/Users/LENOVO/Documents/interfaceClientsansArd/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << CIN+"\n"+NOM << "\n" +NUM_TELEPHONE<< "\n" +EMAIL<< "\n ce client a etait modifier le " +sDate << "\n";


}
void Historique::save2(QString CIN)
{
    QFile file ("C:/Users/LENOVO/Documents/interfaceClientsansArd/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << CIN+"\n"<< "ce client a etait supprimer le " +sDate << "\n";


}
