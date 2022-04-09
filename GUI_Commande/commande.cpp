#include "commande.h"

#define AFFEC(att) do{ this-> att = att ;} while(0)

Commande::Commande() {}

Commande::Commande(int nbArticles, int CIN, double prix, QString dateRecuperation, int ID, int ID_Employe, QString dateDepot, state etat)
{
    AFFEC(ID);
    AFFEC(nbArticles);
    AFFEC(CIN);
    AFFEC(ID_Employe);
    AFFEC(prix);
    AFFEC(dateDepot);
    AFFEC(dateRecuperation);
    AFFEC(etat);
}

//mutateurs

SET(Commande, int, ID)
SET(Commande, int, nbArticles)
SET(Commande, int, ID_Employe)
SET(Commande, int, CIN)
SET(Commande, double, prix)
SET(Commande, QString, dateDepot)
SET(Commande, QString, dateRecuperation)
SET(Commande, state, etat)

//accesseurs

GET(Commande, int, ID)
GET(Commande, int, nbArticles)
GET(Commande, int, ID_Employe)
GET(Commande, int, CIN)
GET(Commande, double, prix)
GET(Commande, QString, dateDepot)
GET(Commande, QString, dateRecuperation)
GET(Commande, state, etat)

//CRUD

bool Commande::ajouter()
{
    QSqlQuery query;

    //convert non-string values to QString to prepare for binding to prepared query

    QString sna=QString::number(nbArticles);
    QString se=QString::number((int)etat);
    QString sp=QString::number(prix);
    QString scin=QString::number(CIN);
    QString sie=QString::number(ID_Employe);

    query.prepare("INSERT INTO COMMANDES (DATERECUPERATION, NBARTICLES, ETAT, PRIX, CIN, ID_EMPLOYE) VALUES (TO_DATE(?,'DD/MM/YYYY'), ?, ?, ?, ?, ?)");
    query.addBindValue(dateRecuperation);
    query.addBindValue(sna);
    query.addBindValue(se);
    query.addBindValue(sp);
    query.addBindValue(scin);
    query.addBindValue(sie);
    return query.exec();
}

QSqlQueryModel * Commande::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM COMMANDES");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Date de Dépot"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Date de Récupératin"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Nombre d'Articles"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("ID de l'employé"));

    return model;
}

bool Commande::modifier(const int &choix)
{
    QSqlQuery query;
    QString sid=QString::number(ID);

    //convert non-string values to QString to prepare for binding to prepared query
    switch(choix)
    {
    case 0:
       {
        query.prepare("UPDATE COMMANDES SET DATERECUPERATION=TO_DATE('?','DD/MM/YYYY') WHERE ID=?");
        query.addBindValue(dateRecuperation);
        query.addBindValue(sid);
        return query.exec();
        break;
       }
    case 1:
        {
        query.prepare("UPDATE COMMANDES SET NBARTICLES=? WHERE ID=?");
        QString sna=QString::number(nbArticles);
        query.addBindValue(sna);
        query.addBindValue(sid);
        return query.exec();
        break;
        }
    case 2:
       {
        query.prepare("UPDATE COMMANDES SET ETAT=? WHERE ID=?");
        QString se=QString::number((int)etat);
        query.addBindValue(se);
        query.addBindValue(sid);
        return query.exec();
        break;
    }
    case 3:
       {
        query.prepare("UPDATE COMMANDES SET PRIX=? WHERE ID=?");
        QString sp=QString::number(prix);
        query.addBindValue(sp);
        query.addBindValue(sid);
        return query.exec();
       }
    }
}

bool Commande::supprimer(const int &ID)
{
    QSqlQuery query;
    QString sid=QString::number(ID);

    query.prepare("DELETE FROM COMMANDES WHERE ID= ?");
    query.addBindValue(sid);
    return query.exec();
}

