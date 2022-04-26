#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class produit
{
public:
    produit();
    produit(int, QString, float,QString, int );
    int get_id();
    QString get_nom();
    float get_prix();
    int get_qte();
    QString get_datee();

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherId();
    bool supprimer(int);
    QSqlQueryModel * afficher_email();
     bool testemail(QString);

    bool modifier(int,int);
    QSqlQueryModel * rechercher(int );
    QSqlQueryModel * afficher_tri_ID();
    QSqlQueryModel * afficher_tri_nom();
    QSqlQueryModel * afficher_tri_quantite();
    QSqlQueryModel * afficher_tri_date();
    QSqlQueryModel * afficher_tri_prix();

    QSqlQueryModel *displayClause(QString cls);

private:


int id;
QString nom;
float prix;
int qte;
QString datee;




};

#endif // PRODUIT_H
