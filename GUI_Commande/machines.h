#ifndef MACHINES_H
#define MACHINES_H

#include<QSqlDatabase>
#include<QSqlQueryModel>
#include<QSqlQuery>
class Machines
{

public:
    Machines();
    Machines(int , QString , QString, QString);
    int getid();
    QString getstate();
    QString getmarque();
    QString getdatea();
    void setid(int) ;
    void setstate(QString) ;
    void setmarque(QString);
    void setdatea (QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int , QString , QString ,QString);
    QSqlQueryModel * recherche(int id);
    QSqlQueryModel* trier(QString attribute , QString croissance );
    void pdf();

    
    
private:
    int id   ;
    QString marque , datea , state;
    
};

#endif // MACHINES_H
