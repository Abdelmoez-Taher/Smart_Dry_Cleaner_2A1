#ifndef COMMANDE_H
#define COMMANDE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDebug>
#include <QSqlError>

#define SETH(type, att) void set_ ## att (type att)

#define GETH(type, att) type get_ ## att ()

#define SET(class, type, att) void class :: set_ ## att (type att){\
        this-> att = att;}

#define GET(class, type, att) type class :: get_ ## att (){return att;}



enum state {invalid=-1 ,waiting=0, ready=1, paid=2};

class Commande
{
    int ID, nbArticles, CIN, ID_Employe;
    double prix;
    QString dateDepot, dateRecuperation;
    state etat;
public:
    //constructeurs
    Commande();
    Commande(int nbArticles, int CIN, double prix, QString dateRecuperation, int ID=-1, int ID_Employe=0, QString dateDepot="", state etat=waiting);

    //mutateurs
    SETH(int, ID);
    SETH(int , nbArticles);
    SETH(int, CIN);
    SETH(int, ID_Employe);
    SETH(QString, dateDepot);
    SETH(QString, dateRecuperation);
    SETH(state, etat);
    SETH(double, prix);

    //accesseurs
    GETH(int, ID);
    GETH(int , nbArticles);
    GETH(int, CIN);
    GETH(int, ID_Employe);
    GETH(QString, dateDepot);
    GETH(QString, dateRecuperation);
    GETH(state, etat);
    GETH(double, prix);

    //CRUD
    bool/*void*/ ajouter();
    static QSqlQueryModel * afficher();
    bool modifier(const int &choix);
    static bool supprimer(const int &ID);
};

#endif // COMMANDE_H
