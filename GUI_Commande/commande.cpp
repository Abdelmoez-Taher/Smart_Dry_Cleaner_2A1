#include "commande.h"

#define AFFEC(att) do{ this-> att = att ;} while(0)


//constructeurs

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

QSqlQueryModel * Commande::search(QString rech)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from commandes where lower(CIN) LIKE lower('%" + rech + "%') OR lower(ID) LIKE lower('%" + rech + "%')");
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
QSqlQueryModel * Commande::TRI(int index)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    switch (index) {
    case 1 :
        model->setQuery("select * from COMMANDES ORDER BY id  ");

        break;
        case 2:
        model->setQuery("select * from COMMANDES ORDER BY id desc  ");

            break;
            case 3 :
        model->setQuery("select * from COMMANDES ORDER BY cin  ");

                break;

                case 4 :
        model->setQuery("select * from COMMANDES ORDER BY cin desc  ");

                    break;

    default:
        model->setQuery("SELECT * FROM COMMANDES");


        }    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
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
        query.prepare("UPDATE COMMANDES SET DATERECUPERATION=TO_DATE(?,'DD/MM/YYYY') WHERE ID=?");
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

bool Commande::IDValid(const int &ID, Commande &C)
{
    QSqlQuery query;
    QString sid=QString::number(ID);
    qDebug() << sid;

    query.prepare("SELECT NBARTICLES, CIN, PRIX, DATERECUPERATION, ID, ID_EMPLOYE, DATEDEPOT, ETAT FROM COMMANDES WHERE ID= ? ");
    query.addBindValue(sid);
    query.exec();
    qDebug() << query.first();
    qDebug() << query.isValid();
    if (query.isValid()) //not before first record or after last record
    {
        qDebug() << query.isValid();
        C.set_nbArticles(query.value(0).toInt());
        C.set_CIN(query.value(1).toInt());
        C.set_prix(query.value(2).toDouble());
        C.set_dateRecuperation(query.value(3).toDate().toString("dd/MM/yyyy"));
        qDebug() << "this is date de recuperation" << query.value(3);
        C.set_ID(query.value(4).toInt());
        C.set_ID_Employe(query.value(5).toInt());
        C.set_dateDepot(query.value(6).toDate().toString("dd/MM/yyyy"));
        C.set_etat((state)(query.value(7).toInt()));
        return true;
    }
    else
        return false;
}

bool Commande::CINValid(const long long int &CIN)
{
    QSqlQuery query;
    QString scin=QString::number(CIN);
    qDebug() << scin;

    query.prepare("SELECT CIN, ID FROM COMMANDES WHERE CIN=?");
    query.addBindValue(scin);
    query.exec();
    query.next();
    qDebug()<<"is it valid?"<<query.isValid();
    return query.isValid();
}
