#include "produit.h"
#include <QSqlQuery>
#include <QString>
#include <QTableView>

produit::produit()
{
    id=0;
    nom="";
    prix=0.0;
    datee="";
    qte=0;


}
produit::produit(int id,QString nom,float prix,QString datee, int qte )
{
    this->id=id;
    this->nom=nom;
    this->prix=prix;
    this->datee=datee;
    this->qte=qte;

}

int produit:: get_id(){return id; }


bool produit:: ajouter()
{
    QSqlQuery query;

    QString res= QString::number(id);
        QString res1= QString::number(qte);
         QString res2= QString::number(prix);
    query.prepare("INSERT INTO PRODUIT (ID,NOM,PRIX,DATEE,QTE) "
                        "VALUES ( :id,:nom,:prix,:datee,:qte)");
    query.bindValue(":id", res);
    query.bindValue(":nom",nom);
    query.bindValue(":prix", res2);
    query.bindValue(":datee",datee);
    query.bindValue(":qte", res1);



    return    query.exec();
    }

QSqlQueryModel *produit::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT  order by ID desc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));



    return model;
}
QSqlQueryModel *produit::afficherId()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id from  PRODUIT  order by ID  ");
    return model;
}
bool produit::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from PRODUIT where ID = :id ");
    query.bindValue(":id", id);
    return    query.exec();
}

bool produit:: modifier(int id ,int qte )
{QSqlQuery query;
    QString res= QString::number(qte);
    QString res1= QString::number(id);

         query.prepare("UPDATE PRODUIT set ID=:id,QTE=:qte where ID= :id ");
         query.bindValue(":id", res1);
         query.bindValue(":qte", res);

        return    query.exec();

}



QSqlQueryModel * produit::rechercher(int id)
{

    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("Select * from PRODUIT where ID =:id");
    query.bindValue(":id",id);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

        return model;
   }

QSqlQueryModel * produit::afficher_tri_ID()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT order by ID asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));

    return model;
}


QSqlQueryModel * produit::afficher_tri_nom()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT order by NOM asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));

    return model;
}

QSqlQueryModel * produit::afficher_tri_quantite()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT order by QTE asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));

    return model;
}

QSqlQueryModel * produit::afficher_tri_date()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT order by DATEE asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));

    return model;
}

QSqlQueryModel * produit::afficher_tri_prix()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT order by PRIX asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));

    return model;
}





QSqlQueryModel *produit::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("QTE"));


    return model;
}

