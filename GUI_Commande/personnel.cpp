#include "personnel.h"
#include <QDebug>
#include <iostream>
#include <list>
#include <QString>
//constructeur par defaut
personnel::personnel()
{
     cin="";
     nom="";
     prenom="";
     date_naissance="";
     adresse="";
     num_tel="";


}
//constructeur parametrique
personnel::personnel(QString cin,QString nom,QString prenom,QString date_naissance,QString adresse,QString num_tel){

    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->date_naissance=date_naissance;
    this->adresse=adresse;

    this->num_tel=num_tel;

}
void personnel::setcin(QString cin1)
{cin=cin1;
}
void personnel::setnom(QString nom)
{this->nom=nom;}
void personnel::setprenom(QString prenom)
{this->prenom=prenom;}
void personnel::setdate_naissance(QString date_naissance)
{this->date_naissance=date_naissance;}
QString personnel::getcin(){return cin;}
QString personnel::getnom(){return nom;}
QString personnel::getprenom(){return prenom;}

QString personnel::getnum_tel(){return num_tel;}
QString personnel::getadresse(){return adresse;}
QString personnel::getdate_naissance(){return date_naissance;}


bool personnel:: ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO PERSONNEL (id_employe,NOM,PRENOM,DATE_NAISSANCE,ADRESSE,NUM_TEL) "
                        "VALUES ( :cin ,:nom,:prenom,:date_naissance,to_date(:adresse,'DD-MM-YYYY'),:num_tel)");
   query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":adresse",adresse);


    return    query.exec();
    }

QSqlQueryModel *personnel::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PERSONNEL  order by CIN desc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));



    return model;
}
bool personnel:: modifier(QString cin ,QString num_tel , QString adresse)
{QSqlQuery query;


         query.prepare("UPDATE PERSONNEL set id_employe=:cin,ADRESSE=:adresse,NUM_TEL=:num_tel where id_employe= :cin ");
         query.bindValue(":cin",cin);
         query.bindValue(":adresse",adresse);
query.bindValue(":num_tel",num_tel);

        return    query.exec();

}


bool personnel::supprimer(QString cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM personnel WHERE id_employe = :cin ");
    query.bindValue(":cin", cin);

    return  query.exec();
}

QSqlQueryModel * personnel::chercher(QString nom)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * from personnel where nom like :nom  ");
    query.bindValue(":nom",nom);


    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("num_tel"));



    return model;
}
QSqlQueryModel* personnel::trie_date_naissance(QString index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select * FROM personnels ORDER BY date_naissance ");
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("num_tel"));


    return model;
}
QSqlQueryModel* personnel::trie_cin(QString index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select * FROM personnel ORDER BY id_employe ");
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("num_tel"));



    return model;
}

QSqlQueryModel * personnel::afficher_tri_CIN()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PERSONNEL order by id_employe desc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TELEPHONE"));

    return model;
}


QSqlQueryModel *personnel::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PERSONNEL " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TELEPHONE"));



    return model;
}
