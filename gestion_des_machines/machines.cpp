#include "machines.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QMessageBox>
#include<QObject>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
Machines::Machines()
{
id=0;  state=" "  ; marque=" "; datea=" ";
}
Machines:: Machines (int id , QString state  , QString marque, QString datea )
{this->id=id;this->state=state;this->marque=marque;this->datea=datea;}
int Machines::getid(){return id ;}
QString Machines::getstate(){return state ;}
QString Machines::getmarque(){return marque ;}
QString Machines::getdatea(){return datea ;}
void Machines:: setid(int id) {this->id=id;}
void Machines:: setstate (QString state){this->state=state;}
void Machines:: setmarque(QString marque){this->marque=marque;}
void Machines:: setdatea (QString datea) {this->datea=datea;}
bool Machines::ajouter()
{


    QSqlQuery query;
    QString id_string=QString::number(id);
          query.prepare("INSERT INTO machines (id, state, marque , datea) "
                        "VALUES (:id, :state, :marque, :datea)");
          query.bindValue(":id", id_string);
          query.bindValue(":state", state);
          query.bindValue(":marque", marque);
          query.bindValue(":datea", datea);

        return query.exec();

}

QSqlQueryModel* Machines::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM machines");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("State"));
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
bool Machines:: modifier(int id , QString state, QString datea, QString marque)
{
    QSqlQuery query;
        QString id_string = QString::number(id);

        query.prepare("update Machines set  state= :state, marque= :marque, datea= :datea WHERE ID = :id");
        query.bindValue(":state", state);
        query.bindValue(":datea", datea);
        query.bindValue(":marque", marque);
        query.bindValue(":id", id);
        return query.exec();
    }
QSqlQueryModel *Machines::recherche(int id)
{
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();
    int c=0;
    query.prepare("SELECT *from Machines where id=:id");
    query.bindValue(":id",id);

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
QSqlQueryModel* Machines::trier(QString attribute , QString croissance ){
        QSqlQueryModel* model = new QSqlQueryModel();
        if(attribute == "ID" && croissance == "croissante")
            model->setQuery("SELECT * FROM MACHINES ORDER BY ID ASC ");
        else if (attribute == "DATEA" && croissance == "croissante")
            model->setQuery("SELECT * FROM MACHINES ORDER BY DATEA ASC ");
        else if(attribute == "ID" && croissance == "decroissant")
            model->setQuery("SELECT * FROM MACHINES ORDER BY ID DESC ");
        else if(attribute == "DATEA" && croissance == "decroissant")
            model->setQuery("SELECT * FROM MACHINES ORDER BY DATEA DESC ");
        else if(attribute == "MARQUE" && croissance == "croissante")
            model->setQuery("SELECT * FROM MACHINES ORDER BY MARQUE ASC ");
        else if(attribute == "MARQUE" && croissance == "decroissant")
            model->setQuery("SELECT * FROM MACHINES ORDER BY MARQUE DESC ");
        return model;
}

void Machines::pdf(){
    QSqlQuery qry;
             qry.prepare("select * from MACHINES");
            if(qry.exec())
            {
                QFile file("E:/Studies/C++ Projet/gestion_des_machines/machines.pdf");
                  file.open(QIODevice::WriteOnly | QIODevice::Text);
                  QTextStream out(&file);
                while(qry.next())
                {
                     out << qry.value(0).toInt() << "," << qry.value(1).toInt()<< "," << qry.value(2).toString()<< "," << qry.value(3).toString()<<  "\n" ;
                }
             }

}

