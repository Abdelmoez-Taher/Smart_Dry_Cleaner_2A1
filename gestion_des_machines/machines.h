#ifndef MACHINES_H
#define MACHINES_H

#include<QSqlDatabase>
#include<QSqlQueryModel>
#include<QSqlQuery>
class Machines
{

public:
    Machines();
    Machines(int , int , QString, QString);
    int getid();
    int getnumserie();
    QString getmarque();
    QString getdatea();
    void setid(int) ;
    void setnumserie(int) ;
    void setmarque(QString);
    void setdatea (QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int , int , QString ,QString);
    QSqlQueryModel * recherche(int numserie);

    
    
private:
    int id , numserie  ;
    QString marque , datea;
    
};

#endif // MACHINES_H
