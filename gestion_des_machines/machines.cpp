#include "machines.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QMessageBox>
#include<QObject>
Machines::Machines()
{
id=0;  numserie=0 ; marque=" "; datea=" ";
}
Machines:: Machines (int id , int numserie  , QString marque, QString datea )
{this->id=id;this->numserie=numserie;this->marque=marque;this->datea=datea;}
int Machines::getid(){return id ;}
int Machines::getnumserie(){return numserie ;}
QString Machines::getmarque(){return marque ;}
QString Machines::getdatea(){return datea ;}
void Machines:: setid(int id) {this->id=id;}
void Machines:: setnumserie (int numserie){this->numserie=numserie;}
void Machines:: setmarque(QString marque){this->marque=marque;}
void Machines:: setdatea (QString datea) {this->datea=datea;}
bool Machines::ajouter()
{


    QSqlQuery query;
    QString id_string=QString::number(id);
    QString numserie_string=QString::number(numserie);
          query.prepare("INSERT INTO machines (id, numserie, marque , datea) "
                        "VALUES (:id, :nums, :marque, :datea)");
          query.bindValue(":id", id_string);
          query.bindValue(":nums", numserie_string);
          query.bindValue(":marque", marque);
          query.bindValue(":datea", datea);

        return query.exec();

}

QSqlQueryModel* Machines::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM machines");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero du serie"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date D'achat"));

    return model;

}
bool Machines::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE from machines where id=:id");
    query.bindValue(0, id);


  return query.exec();

}
bool Machines:: modifier(int id , int numserie, QString datea, QString marque)
{
    QSqlQuery query;
        QString id_string = QString::number(id);
        QString numserie_string = QString::number(numserie);

        query.prepare("update Machines set  numserie= :nums, marque= :marque, datea= :datea WHERE ID = :id");
        query.bindValue(":nums", numserie);
        query.bindValue(":datea", datea);
        query.bindValue(":marque", marque);
        query.bindValue(":id", id);
        return query.exec();
    }
QSqlQueryModel *Machines::recherche(int numserie)
{
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();
    int c=0;
    query.prepare("SELECT *from Machines where numserie=:numserie");
    query.bindValue(":numserie",numserie);

    if(query.exec())
    {
        while(query.next())
        {
            c++;
        }

        if(c==1)
        {
            QMessageBox boxt;
            boxt.setText("trouvé");
            boxt.exec();
            model->setQuery(query);
        }
        else
            if (c<1)
            {
                QMessageBox boxpt;
                boxpt.setText("pas trouvé");
                boxpt.exec();
                model=0;
            }
        return model;
    }

}
