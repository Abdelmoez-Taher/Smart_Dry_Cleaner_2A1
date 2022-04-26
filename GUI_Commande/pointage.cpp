#include "pointage.h"

#define AFFEC(att) do{ this-> att = att ;} while(0)


const QTime Pointage::entreev=QTime::fromString("08:00:00","HH:mm:ss");
const QTime Pointage::sortiev=QTime::fromString("17:00:00","HH:mm:ss");
long long int Pointage::RFID[2]={310988016, 157514120126};

//constructeurs
Pointage::Pointage(){}

Pointage::Pointage(int ID_Employe, QTime sortie, int assiduite, QTime entree, QDate datePointage)
{
    AFFEC(ID_Employe);
    AFFEC(datePointage);
    AFFEC(entree);
    AFFEC(sortie);
    if (assiduite==-1)
    {
        if ( (this->entree > entreev) && (this->entree <= entreev.addSecs(9*60*60)) ) //16h
            assiduite= RETARD;
       else if (this->entree > entreev.addSecs(9*60*60))
           assiduite= ABSENT;
       else
           assiduite= PRESENT;
    }
    else
    {
        if(this->sortie < sortiev)
            assiduite |= ABANDONPOSTE;
        AFFEC(assiduite);
    }
}

//mutateurs
SET(Pointage,int, ID_Employe)
SET(Pointage, QDate, datePointage)
SET(Pointage, QTime, entree)
void Pointage::set_sortie(const QTime & sortie)
{
    this->sortie=sortie;
    if(this->sortie < sortiev)
        assiduite |= ABANDONPOSTE;
}

//accesseurs
GET(Pointage,int, ID_Employe)
GET(Pointage, QDate, datePointage)
GET(Pointage, QTime, entree)
GET(Pointage, QTime, sortie)

//CRUD

bool Pointage::ajouter()
{
    QSqlQuery query;

    //convert non-string values to QString to prepare for binding to prepared query

    QString sie=QString::number(ID_Employe);
    QString sdp=datePointage.toString("dd/MM/yyyy");
    QString se=entree.toString("HH:mm:ss");
    QString sa=QString::number(assiduite);

    query.prepare("INSERT INTO POINTAGE (ID_EMPLOYE, DATEP, ENTREE, ASSIDUITE) VALUES (?, TO_DATE(?,'DD/MM/YYYY'), ?, ?)");
    query.addBindValue(sie);
    query.addBindValue(sdp);
    query.addBindValue(se);
    query.addBindValue(sa);
    return query.exec();
}

bool Pointage::modifier()
{
QSqlQuery query;
QString ss=sortie.toString("HH:mm:ss");
QString sie=QString::number(ID_Employe);
QString sdp=datePointage.toString("dd/MM/yyyy");
QString sa=QString::number(assiduite);

//prendre la requête en paramètre et la préparer pour l'execution
query.prepare("UPDATE POINTAGE SET SORTIE=?, ASSIDUITE=? WHERE ID_EMPLOYE=? AND DATEP=?");

//création des variables liées
query.addBindValue(ss);
query.addBindValue(sa);
query.addBindValue(sie);
query.addBindValue(sdp);

return query.exec(); //exec() envoie la requête pour l'exécuter
}

QSqlQueryModel * Pointage::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM COMMANDES");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID d'employé"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Date du pointage"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Heure d'entrée"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Heure de sortie"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Assiduité"));

    return model;
}

int Pointage::pointageValid(const int &ID_Employe/*, const int &assiduite*/)
{
    QSqlQuery query;
    QString sie=QString::number(ID_Employe);
    QString sdp=QDate::currentDate().toString("dd/MM/yyyy");
    //QString sa=QString::number(assiduite);
    qDebug() << "ceci est l'ID employé obtenu à travers le RFID"<<sie;
    qDebug() << "ceci est la date d'aujourd'hui utilisée dans la clé primaire de pointage"<<sdp;
    query.prepare("SELECT ID_EMPLOYE, DATEP, ENTREE, SORTIE, ASSIDUITE FROM POINTAGE WHERE ID_EMPLOYE=? AND DATEP=TO_DATE(?,'DD/MM/YYYY') ");
    query.addBindValue(sie);
    query.addBindValue(sdp);
    query.exec();
    query.next();
    qDebug() <<"pointageValid query.isValid() returns the following"<< query.isValid();
    if (!(query.isValid())) //before first record or after last record
                return -1;
    else
    {
        if (query.value(3).toString()=="23:59:59")
            return 0;
        else
            return 1;
    }
}

int Pointage::IDEmfromRFID(const long long int &RFID)
{
    QSqlQuery query;
    QString srfid=QString::number(RFID);
    qDebug()<<"this is srfid the rfid we're getting the ID by"<<srfid;
    query.prepare("SELECT ID_EMPLOYE FROM PERSONNEL WHERE RFID=?");
    query.addBindValue(srfid);
    query.exec();
    return query.value(0).toInt();
}

bool Pointage::checkAbsence()
{
    QSqlQuery query;
    query.prepare(/*"\
                  INSERT INTO POINTAGE (ID_EMPLOYE, DATEP, ENTREE, SORTIE, ASSIDUITE)\
                  SELECT PERSONNEL.ID_EMPLOYE, POINTAGE.DATEP, '00:00:00', '00:00:00', 4\
                  FROM PERSONNEL, POINTAGE\
                  WHERE POINTAGE.DATEP=SYSDATE\
                  MINUS\
                  SELECT PERSONNEL.ID_EMPLOYE, POINTAGE.DATEP, '00:00:00', '00:00:00', 4\
                  FROM PERSONNEL INNER JOIN POINTAGE\
                  ON PERSONNEL.ID_EMPLOYE=POINTAGE.ID_EMPLOYE\
                  WHERE POINTAGE.DATEP=SYSDATE;\
                  "*/

                  "INSERT INTO POINTAGE (ID_EMPLOYE, DATEP, ENTREE, SORTIE, ASSIDUITE)\
                  SELECT PERSONNEL.ID_EMPLOYE, POINTAGE.DATEP, '00:00:00', '23:59:59', 4\
                  FROM PERSONNEL LEFT OUTER JOIN POINTAGE\
                  ON PERSONNEL.ID_EMPLOYE=POINTAGE.ID_EMPLOYE\
                  WHERE POINTAGE.DATEP=SYSDATE AND POINTAGE.ID_EMPLOYE IS NULL ;"
                  );
    return query.exec();
}

int Pointage::AssidfromPKey(const int &ID_Employe)
{
    QSqlQuery query;
    QString sie=QString::number(ID_Employe);
    QString sdp=QDate::currentDate().toString("dd/MM/yyyy");
    query.prepare("SELECT ASSIDUITE FROM POINTAGE WHERE ID_EMPLOYE=? AND DATEP=?");
    query.addBindValue(sie);
    query.addBindValue(sdp);
    query.exec();
    return query.value(0).toInt();
}

bool Pointage::checkAccess(const long long int &RFID)
{
    QSqlQuery query;
    QString srfid=QString::number(RFID);
    qDebug()<<"this is srfid the rfid which existence we're checking in table personnel"<<srfid;
    query.prepare("SELECT * FROM PERSONNEL WHERE RFID=?");
    query.addBindValue(srfid);
    query.exec();
    query.next();
    qDebug()<<"checks if there is the rfid in table personnel"<<query.isValid();
    return query.isValid();
}
