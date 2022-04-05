#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machines.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QTextStream>
#include <QDataStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QRegularExpressionValidator>
#include <QPainter>
#include <QFileDialog>
#include "connection.h"
#include <qdebug.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Connection c;
    Machines m;
    c.createconnection();
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator (0, 99999999, this));
    ui->tab_machine->setModel(m.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_le_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();
    QString state=ui->le_numserie->text();
    QString marque=ui->le_marque->text();
    QString datea=ui->le_date->text();
    Machines M(id, state , marque , datea);
    bool test=M.ajouter();
    if(test)
{
       { QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_machine->setModel(M.afficher());
        }

}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT Ok"),
                    QObject::tr("Ajout non effecute.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }



void MainWindow::on_le_supprimer_clicked()
{
    Machines M1 ; M1.setid(ui->le_id_supp->text().toInt());
    bool test=M1.supprimer(M1.getid());
    if(test)
{
        { QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        ui->tab_machine->setModel(M.afficher());

        }
}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT Ok"),
                    QObject::tr("Suppression non effecute.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
void MainWindow::on_le_modifier_clicked()
{
    QString marque = ui->le_upmarque->text();
    QString datea = ui->le_update->text();
    QString state = ui->le_upnums->text();
    int id = ui->le_upid->text().toInt();

   bool test =  M.modifier(id,state,datea,marque);

    if(test){
        ui->tab_machine->setModel(M.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("update effectué\n""Click to Cancel."),
                                 QMessageBox::Cancel);     }
    else         QMessageBox::critical  (nullptr, QObject::tr("not OK"),
                 QObject::tr("update non effectué\n""Click to Cancel."), QMessageBox::Cancel);
}



void MainWindow::on_le_trier_clicked()

    {
        QString attribute = ui->attributebox->currentText();
        QString croissance = ui->croicbox->currentText();
        ui->tab_machine->setModel(M.trier(attribute,croissance));
        qDebug() << attribute << croissance;
    }



void MainWindow::on_le_recherche_clicked()
{
    {
        Machines m;
             ui->tableView->setModel(m.recherche(ui->le_cherche->text().toInt()));
             ui->le_cherche->clear();

}
}


void MainWindow::on_le_pdf_clicked()
{
    Machines m;
    m.pdf();
}
