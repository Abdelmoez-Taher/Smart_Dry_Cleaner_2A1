#ifndef POINTAGE_H
#define POINTAGE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include <QDate>
#include <QTime>
#include <string>


#define SETH(type, att) void set_ ## att (type att)

#define GETH(type, att) type get_ ## att ()

#define SET(class, type, att) void class :: set_ ## att (type att){\
        this-> att = att;}

#define GET(class, type, att) type class :: get_ ## att (){return att;}

#define PRESENT 0

#define RETARD 1

#define ABANDONPOSTE 2

#define ABSENT 4

class Pointage
{
    const int a=5;
    int ID_Employe, assiduite;
    QDate datePointage;
    QTime entree, sortie;
    int numRFID=2;


public:

    static const QTime entreev;
    static const QTime sortiev;
    static long long int RFID[2];

    //constructeurs
    Pointage();
    Pointage(int ID_Employe, QTime sortie=QTime::fromString("23:59:59","HH:mm:ss"), int assiduite=-1, QTime entree= QTime::currentTime(), QDate datePointage= QDate::currentDate());

    //mutateurs
    SETH(int, ID_Employe);
    SETH(QDate, datePointage);
    SETH(QTime, entree);
void set_sortie(const QTime &sortie);
    SETH(int, assiduite);

    //accesseurs
    GETH(int, ID_Employe);
    GETH(QDate, datePointage);
    GETH(QTime, entree);
    GETH(QTime, sortie);
    GETH(int, assiduite);

    //CRUD
    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    static int pointageValid(const int &ID_Employe/*, const int &assiduite*/);
    static int IDEmfromRFID(const long long int &RFID); //attention! cette méthode doit être déclarée et implémentée dans la classe employé
    static int AssidfromPKey(const int &ID_Employe);
    static bool checkAbsence();
    static bool checkAccess(const long long int &RFID);
};

#endif // POINTAGE_H
