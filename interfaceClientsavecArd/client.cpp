#include "client.h"
#include<QString>
#include<QtSql/QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QtSql/QSqlQueryModel>
#include<QPdfWriter>
#include<QPainter>
#include<QMessageBox>
#include<QSystemTrayIcon>

//constructeur sans parametre
client::client()
{

    CIN=0;
    NOM=" ";
    PRENOM=" ";
    NUM_TELEPHONE="";
    EMAIL="";


}
//constructeur avec parametre
client::client(int CIN,QString NOM,QString PRENOM,QString NUM_TELEPHONE,QString EMAIL)
{
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->CIN=CIN;
    this->NUM_TELEPHONE=NUM_TELEPHONE;
    this->EMAIL=EMAIL;



}

//les getters
int client::getCIN(){return CIN;}
QString client::getNOM(){return NOM;}
QString client::getPRENOM(){return PRENOM;}
QString client::getNUM_TELEPHONE(){return NUM_TELEPHONE;}
QString client::getEMAIL(){return EMAIL;}


//les setters

void client::setCIN(int CIN){this->CIN=CIN ;}
void client::setNOM(QString NOM){this->NOM=NOM   ;}
void client::setPRENOM(QString PRENOM){this->PRENOM=PRENOM   ;}
void client::setNUM_TELEPHONE(QString NUM_TELEPHONE){this->NUM_TELEPHONE=NUM_TELEPHONE ;}
void client::setEMAIL(QString EMAIL){this->EMAIL=EMAIL  ;}


bool client::ajouter()
{
    bool test=false;
    QSqlQuery query;

        QString CIN_string=QString::number(CIN);

          query.prepare("INSERT INTO CLIENT (CIN,NOM,PRENOM,NUM_TELEPHONE,EMAIL) VALUES (:CIN, :NOM, :PRENOM  , :NUM_TELEPHONE , :EMAIL)");
          query.bindValue(":CIN" , CIN_string);
          query.bindValue(":NOM" , NOM);
          query.bindValue(":PRENOM", PRENOM);
          query.bindValue(":NUM_TELEPHONE", NUM_TELEPHONE);
          query.bindValue(":EMAIL" ,EMAIL);

          query.exec();
    return test;
}


QSqlQueryModel * client ::afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from CLIENT");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TELEPHONE "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL "));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));

        return model;
}

bool client::modifierj(int CIN ,QString NOM , QString PRENOM  ,QString NUM_TELEPHONE,QString EMAIL)
{
    QSqlQuery query;

    query.prepare("UPDATE CLIENT SET NOM= :NOM,PRENOM= :PRENOM, NUM_TELEPHONE= :NUM_TELEPHONE , EMAIL= :EMAIL  where CIN= :CIN ");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":NUM_TELEPHONE",NUM_TELEPHONE);
    query.bindValue(":EMAIL",EMAIL);

            return    query.exec();
}


bool client:: supprimer(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);
    query.prepare("Delete from client where CIN=:cin");
    query.bindValue(":cin",res);
    return query.exec();
}
QSqlQueryModel* client::afficherTriCINAsc()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM CLIENT ORDER BY CIN");

   model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_TELEPHONE"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));



  return  model;
}

QSqlQueryModel* client::afficherTriCINDesc()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM CLIENT ORDER BY CIN desc");
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_TELEPHONE"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));


  return  model;
}

QSqlQueryModel * client::afficherTriNOM()
{
    QSqlQueryModel* model=new QSqlQueryModel();


     model->setQuery("SELECT* FROM CLIENT ORDER BY NOM");
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_TELEPHONE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));



    return  model;
}

QString client::VenteFlash()
{
    QSqlQuery query;
         query.prepare("update commande inner join client set commandes.prix=commandes.prix*0.1 where commandes.ID = client.CIN AND commandes.prix>50");
        query.exec();
}
