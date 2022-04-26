#ifndef PERSONNEL_H
#define PERSONNEL_H

#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class personnel
{
public:
    personnel();
    personnel(QString cin,QString nom,QString prenom,QString date_naissance,QString Adresse,QString num_tel );

     QString getcin();
     QString getnom();
     QString getprenom();
     QString getnum_tel();
     QString getadresse();
     QString getdate_naissance();
     void setcin(QString);
     void setnom(QString);
     void setprenom(QString);
     void setadresse(QString);
     void setnumtel(QString);
     void setdate_naissance(QString);

     bool modifier(QString,QString,QString);
      bool ajouter();
      QSqlQueryModel * afficher();
      bool supprimer(QString);
      QSqlQueryModel *chercher(QString nom);

      QSqlQueryModel * afficher_tri_CIN();


       QSqlQueryModel *displayClause(QString cls);
       QSqlQueryModel* trie_date_naissance(QString index);
       QSqlQueryModel* trie_cin(QString index);

      void on_QRcodecom_pressed();

 private :
    QString cin;
    QString nom ;
    QString prenom;
    QString adresse;
    QString num_tel;
    QString date_naissance;

};

#endif // PERSONNEL_H
