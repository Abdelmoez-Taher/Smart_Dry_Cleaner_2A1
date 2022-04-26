#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QTextStream>
#include <QComboBox>
#include <QTabWidget>
#include"QDate"
#include <QDebug>
#include <list>
#include "personnel.h"
#include <QTextBrowser>
#include <QAxObject>

#include<QSystemTrayIcon>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QTextStream>
#include <QComboBox>
#include <QTabWidget>
#include"QDate"
#include <QDebug>
#include <list>
#include <QTextBrowser>
#include "personnel.h"
#include "qrcode.hpp"
#include<QSystemTrayIcon>
#include <QPainter>
#include <QAbstractItemView>
#include"qrcode.hpp"
#include<QTextStream>
#include<QFile>
#include<QFileDialog>
#include <QList>
#include<QtSvg/QSvgRenderer>
#include <string>
#include <vector>
#include<QDirModel>
#include<QAxWidget>
#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include<QSqlQuery>
#include<QRegularExpression>
#include <QPainter>

#include <QSqlQueryModel>

#include <QSystemTrayIcon>


#include <QTextStream>

#include<QDirModel>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

using std::uint8_t;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabperso->setModel(tmpperso.afficher());
    ui->cin->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->numtel->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->salaire->setValidator( new QIntValidator(300, 50000, this));
    QStringList liste;
    liste <<"directeur "<<"caissier"<<"maquilleur"<<"hairstylist"<<"technicien"<<"responsable marketing"<<"responsable RH"<<"assistant";
    ui->poste->addItems(liste);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_add_clicked()
{
      QString cin = ui->cin->text();
      QString nom = ui->nom->text();
      QString prenom = ui->prenom->text();
      QString salaire = ui->salaire->text();
      QString poste = ui->poste->currentText();
      QString adresse = ui->adresse->text();
      QString age = ui->age->text();
      QString num_tel = ui->numtel->text();



        if(cin=="")
        {
         QMessageBox::information(nullptr,QObject::tr("Ajouter un personnel"),QObject::tr("Merci de remplir les champs"),QMessageBox::Ok);
        }
         else {

         personnel p(cin,nom,prenom,salaire,poste,adresse,age,num_tel);

         bool test=p.ajouter();

           if(test)
           {p.ajouter();}
           if(test)
           {ui->tabperso->setModel(tmpperso.afficher());
               QMessageBox::information(nullptr, QObject::tr("Ajouter un personnel"),
                                        QObject::tr("personnel ajouté.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);

           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Ajouter un personnel"),
                                     QObject::tr("Erreur !.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow::on_mod_clicked()
{   QString cin = ui->cin->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
     QString salaire = ui->salaire->text();
     QString poste = ui->poste->currentText();
     QString num_tel = ui->numtel->text();
      QString adresse = ui->adresse->text();
      QString  age=ui->age->text();

      if(cin=="")
      {
       QMessageBox::information(nullptr,QObject::tr("Ajouter un personnel"),QObject::tr("Champ vide"),QMessageBox::Ok);
      }
       else {
        personnel t ;
        bool atout=t.modifier(cin,nom,prenom,salaire,poste,num_tel,adresse,age);
        if(atout)
        {ui->tabperso->setModel(tmpperso.afficher());
            QMessageBox::information(nullptr, QObject::tr("modifier un personnel "),
                                     QObject::tr("table modifié.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier un personnel "),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
}
}
void MainWindow::on_supp_clicked()
{
    QString cin=ui->cinmod_3->text();
    if(cin=="")
    {
     QMessageBox::information(nullptr,QObject::tr("Ajouter un personnel"),QObject::tr("Merci d'écrire le CIN "),QMessageBox::Ok);
    }
     else {
       bool test=tmpperso.supprimer(cin);
           if(test)
           {ui->tabperso->setModel(tmpperso.afficher());

               QMessageBox::information(nullptr, QObject::tr("supprimer un personnel"),
                                        QObject::tr("personnel supprimer.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);}
           else
              QMessageBox::critical(nullptr, QObject::tr("Supprimer un personnel"),
                                   QObject::tr("Erreur !.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow::on_mod_3_clicked()
{
    QString cin = ui->cin->text();
       QString nom = ui->nom->text();
       QString prenom = ui->prenom->text();
        QString salaire = ui->salaire->text();
        QString poste = ui->poste->currentText();
        QString num_tel = ui->numtel->text();
         QString adresse = ui->adresse->text();
         QString age = ui->age->text();


         if(cin=="")
          {
          QMessageBox::information(nullptr,QObject::tr("Ajouter un personnel"),QObject::tr("Merci de remplir les champs"),QMessageBox::Ok);
              }
          else {
           personnel t ;
           bool atout=t.modifier(cin,nom,prenom,salaire,poste,num_tel,adresse,age);
           if(atout)
              { ui->tabperso->setModel(tmpperso.afficher());
               QMessageBox::information(nullptr, QObject::tr("modifier un personnel "),
                                        QObject::tr("table modifié.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);}
           else

               QMessageBox::critical(nullptr, QObject::tr("Modifier un personnel "),
                                     QObject::tr("Erreur !.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_pushButton_4_clicked()
{
    QString nom=ui->lineEdit_idch_2->text();
    QString salaire=ui->lineEdit_idch_2->text();
    QString poste=ui->lineEdit_idch_2->text();


           ui->tabperso->setModel(tmpperso.chercher(nom,salaire,poste));


}








void MainWindow::on_pushButton_trid_clicked()
{
    ui->tabperso->setModel(tmpperso.trie(0));

}

void MainWindow::on_tri_salaire_clicked()
{
        ui->tabperso->setModel(tmpperso.trie_salaire(0));
}



void MainWindow::on_tabperso_clicked(const QModelIndex &index)
{

    QVariant cin=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),1));
    QString rescin=cin.toString();
           ui->cin->setText(rescin);
            QVariant nom=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),2));
            QString resnom=nom.toString();
            ui->nom->setText(resnom);
            QVariant prenom=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),3));
            QString resprenom=prenom.toString();
            ui->prenom->setText(resprenom);
            QVariant adresse=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),4));
            QString resadresse=adresse.toString();
            ui->adresse->setText(resadresse);
            QVariant salaire=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),5));
            QString ressalaire=salaire.toString();
           ui->salaire->setText(ressalaire);
           QVariant numtel=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),6));
           QString resnumtel=numtel.toString();
          ui->numtel->setText(resnumtel);
          QVariant age=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),7));
          QString resage=age.toString();
         ui->age->setText(resage);
    //     QVariant poste=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),3));
       //  QString resposte=poste.toString();
      //  ui->poste->(resposte);


}





/*void MainWindow::on_QRcodecom_clicked()
{
    if(ui->tabperso->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir un personnel du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int id=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->qrcodecommande->setPixmap(pix);
               }
}*/



void MainWindow::on_QRcodecom_3_clicked()
{
    QString File="C:\\Users\\ASUS\\OneDrive\\Bureau\\excel.xlsx";
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks=excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Open (const QString&)", File);
}

void MainWindow::on_pushButton_5_clicked()
{
    personnel A;

      if(ui->tabperso->currentIndex().row()==-1)
                 QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                          QObject::tr("Veuillez Choisir un animal du Tableau.\n"
                                                      "Click Ok to exit."), QMessageBox::Ok);
             else
             {

                                 A.setnom(ui->nom ->text());
                                 A.setprenom(ui->prenom ->text());
                                 A.setage(ui->age ->text());
                              //   A.setnum_tel(ui->tele->text().toInt());



                  //int cin=ui->tab_athltes->model()->data(ui->tab_athltes->model()->index(ui->tab_athltes->currentIndex().row(),0)).toInt();

                                 QString  rawQr = "ID_ANIMAL:%1 Nom_ANIMAL:%2 TYPE_ANIMAL:%3 AGE_ANIMAL:%4 PAYS:%5 REGIME_ALIMENT:%6 " ;
                                    rawQr = rawQr.arg(A.getnom()).arg(A.getprenom().arg(A.getage()));
                                    QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);
                 // const QrCode qr = QrCode::encodeText(std::to_string(cin).c_str(), QrCode::Ecc::LOW);
                  std::ofstream myfile;
                  myfile.open ("qrcode.svg") ;
                  myfile << qr.toSvgString(1);
                  myfile.close();
                  QSvgRenderer svgRenderer(QString("qrcode.svg"));
                  QPixmap pix( QSize(120, 120) );
                  QPainter pixPainter( &pix );
                  svgRenderer.render( &pixPainter );
                  ui->qrcodecommande->setPixmap(pix);

}
}
