#include "form.h"
#include "ui_form.h"
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
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QLabel>
#include <QtPrintSupport/QPrintDialog>
#include<QSystemTrayIcon>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <excel.h>
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
#include <QtPrintSupport/QPrinter>
#include <QSqlQueryModel>
#include <QDesktopServices>
#include <QSystemTrayIcon>

#include<QSystemTrayIcon>
#include <QAxWidget>
#include <QAxObject>
#include "qrcode.hpp"
#include <iostream>
#include <fstream>
#include "exportexcelobjet.h"
#include <QFileDialog>

#include <QTextStream>

#include <QSystemTrayIcon>


#include <QTextStream>

#include<QDirModel>

#include <QIntValidator>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>
#include <QStringList>
#include <QPdfWriter>
#include <QPainter>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QLabel>
#include <QtPrintSupport/QPrintDialog>

#include<QSystemTrayIcon>
#include <QAxWidget>
#include <QAxObject>

#include <iostream>
#include <fstream>

#include <QFileDialog>
#include <excel.h>
#include <arduino.h>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

using std::uint8_t;
#include<QDirModel>


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

        ui->tabperso->setModel(tmpperso.afficher());
        ui->comboBox->setModel(tmpperso.afficher());
        ui->cin->setValidator( new QIntValidator(00000000, 99999999, this));
        ui->numtel->setValidator( new QIntValidator(00000000, 99999999, this));

        // arduino
              int ret=A.connect_arduino();
              switch(ret){
              case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();
                  break;
              case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
                  break;
              case(-1):qDebug()<< "arduino is not availble";
              }
              QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

              //fin arduino

        }




        //arduino

        void Form::update_label()
        {
            data=A.read_from_arduino();
            QString DataAsString = QString(data);
            qDebug()<< data;

             ui->label_2->setText(data);

        }

        //fin arduino


Form::~Form()
{
    delete ui;
}
void Form::on_add_clicked()
{
    bool test;
       QString cin= ui->cin->text();
       QString nom= ui->nom->text();
       QString prenom= ui->prenom->text();
       QString date_naissance=ui->date_naissance->text();
       QString adresse= ui->adresse->text();
       QString num_tel= ui->numtel->text();


       if(nom==""|| prenom==""||cin==0||cin>99999999||nom.length()>10||num_tel==0)


                   {
                                 QMessageBox::critical(nullptr, QObject::tr("vide"),
                                 QObject::tr("veuillez saisir tous les champs correctement!\n"), QMessageBox::Cancel);
                                 test=false;

                   }
       else{
       personnel p(cin,nom,prenom,date_naissance,adresse,num_tel);

        test=p.ajouter();}
        if(test)
        {

            ui->tabperso->setModel(tmpperso.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Ajouter un personnel"),
                              QObject::tr("personnel ajouté.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

            }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter un personnel"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}


void Form::on_supp_clicked()
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

void Form::on_mod_3_clicked()
{
    QString cin= ui->comboBox->currentText();
     QString adresse=ui->lineEdit->text();
    QString num_tel=ui->lineEdit_2->text();



  bool test=tmpperso. modifier( cin,adresse,num_tel );

     if (test)
     { ui->comboBox->setModel(tmpperso.afficher());
         ui->tabperso->setModel(tmpperso.afficher());//refresh
         QMessageBox::information(nullptr, QObject::tr("Modifier un personnel"),
                     QObject::tr("Personnel modifié.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Modifier un personnel"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}


void Form::on_pushButton_4_clicked()
{
    QString nom=ui->lineEdit_idch_2->text();



    ui->tabperso->setModel(tmpperso.chercher(nom));


}








//void Form::on_pushButton_trid_clicked()
//{
//    ui->tabperso->setModel(tmpperso.trie(0));

//}

//void Form::on_tri_salaire_clicked()
//{
   //     ui->tabperso->setModel(tmpperso.trie_salaire(0));
//}



void Form::on_tabperso_clicked(const QModelIndex &index)
{

    QVariant cin=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),0));
    QString rescin=cin.toString();
           ui->cin->setText(rescin);
            QVariant nom=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),1));
            QString resnom=nom.toString();
            ui->nom->setText(resnom);
            QVariant prenom=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),2));
            QString resprenom=prenom.toString();
            ui->prenom->setText(resprenom);
            QVariant date_naissance=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),6));
            //QString resdate_naissance=date_naissance.toString();
          // ui->date_naissance->setText(resdate_naissance);
            QVariant adresse=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),5));
            QString resadresse=adresse.toString();
            ui->adresse->setText(resadresse);
           QVariant numtel=ui->tabperso->model()->data(ui->tabperso->model()->index(ui->tabperso->currentIndex().row(),7));
           QString resnumtel=numtel.toString();
          ui->numtel->setText(resnumtel);




}





















void Form::on_QRcodecom_clicked()


{

    personnel A;

     if(ui->tabperso->currentIndex().row()==-1)
                QMessageBox::information(nullptr, QObject::tr("QR"),
                                         QObject::tr("Veuillez Choisir un personnel du Tableau.\n"
                                                     "Click Ok to exit."), QMessageBox::Ok);
            else
            {


/*
        QString cin = ui->cin->text();
            QString nom = ui->nom->text();
            QString prenom = ui->prenom->text();
            QString numtel = ui->numtel->text();
            QString adresse = ui->adresse->text();

            QString date_naissance = ui->date_naissance->text();*/




         A.setcin(ui-> cin ->text());
         A.setnom(ui->nom ->text());
         A.setprenom(ui->prenom ->text());

         A.setdate_naissance(ui->date_naissance->text());










                                QString  rawQr = "%0cin: %1Nom: %2Prenom:%3date_naissance:%4";
                                 rawQr = rawQr.arg(A.getcin()).arg(A.getnom()).arg(A.getprenom()).arg(A.getdate_naissance());
                                   QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);
                // const QrCode qr = QrCode::encodeText(std::to_string(cin).c_str(), QrCode::Ecc::LOW);
                                   QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                                      for (int y = 0; y < qr.getSize(); y++) {
                                          for (int x = 0; x < qr.getSize(); x++) {
                                              int color = qr.getModule(x, y);  // 0 for white, 1 for black

                                              // You need to modify this part
                                              if(color==0)
                                                  im.setPixel(x, y,qRgb(254, 254, 254));
                                              else
                                                  im.setPixel(x, y,qRgb(0, 0, 0));
                                          }
                                      }
                                      im=im.scaled(200,200);
                                      ui->qrlabel->setPixmap(QPixmap::fromImage(im));
}
}









void Form::on_pdf_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
               QPdfWriter pdf("C:/Users/hamza/Desktop/PDF/Pdf.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste Des Personnels ");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 50));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"CIN");
                   painter.drawText(1700,3300,"NOM");
                   painter.drawText(3200,3300,"PRENOM");
                   painter.drawText(4900,3300,"DATE_NAISSANCE");
                   painter.drawText(6600,3300,"ADRESSE");
                   painter.drawText(8100,3300,"NUM_TEL");

                   QSqlQuery query;
                   query.prepare("select * from PERSONNEL");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1700,i,query.value(1).toString());
                       painter.drawText(3200,i,query.value(2).toString());
                       painter.drawText(4700,i,query.value(3).toString());
                       painter.drawText(6200,i,query.value(4).toString());
                       painter.drawText(7700,i,query.value(5).toString());

                      i = i + 500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {
                           QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/hamza/Desktop/PDF/Pdf.pdf"));
                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }

}

void Form::on_CIN_clicked()
{
    ui->tabperso->setModel( tmpperso.afficher_tri_CIN());
}




void Form::on_exel_clicked()
{





    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                            tr("Excel Files (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tabperso);

            obj.addField(0, "CIN", "char(20)");
            obj.addField(1, "NOM", "char(20)");
            obj.addField(2, "PRENOM", "char(20)");
            obj.addField(3, "DATE_NAISSANCE", "char( 50)");
            obj.addField(4, "ADRESS", "char(20)");
            obj.addField(5, "NUM_TEL", "char(20)");




            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                QMessageBox::information(this, tr("Done"),
                                         QString(tr("%1 records exported!")).arg(retVal)
                                         );
            }

















}

void Form::on_pushButton_clicked()
{

    A.write_to_arduino("1") ;
}

void Form::on_pushButton_2_clicked()
{
      A.write_to_arduino("0") ;
}
