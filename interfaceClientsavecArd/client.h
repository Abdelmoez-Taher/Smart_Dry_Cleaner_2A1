#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include<QString>
#include<QtSql/QSqlQuery>
#include<QTableWidget>
#include<QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>

class client
{
public:

   client();
   client(int,QString,QString,QString,QString);

   int getCIN();
   QString getNOM();
   QString getPRENOM();
   QString getNUM_TELEPHONE();
   QString getEMAIL();

   void setCIN(int);
   void setNOM(QString);
   void setPRENOM(QString);
   void setNUM_TELEPHONE(QString);
   void setEMAIL(QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherTriCINAsc();
    QSqlQueryModel * afficherTriCINDesc();
    QSqlQueryModel * afficherTriNOM();
    QString VenteFlash();
 bool modifierj(int CIN ,QString NOM , QString PRENOM ,QString NUM_TELEPHONE ,QString EMAIL);
 bool supprimer(int);



private :
  QString NOM,PRENOM;
  QString EMAIL;
  int CIN ;
  QString NUM_TELEPHONE;

};


#endif // CLIENT_H
