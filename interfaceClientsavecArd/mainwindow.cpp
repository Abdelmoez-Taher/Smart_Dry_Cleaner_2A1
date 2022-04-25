#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>
#include<QIntValidator>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QDate>
#include<QTableWidget>
#include<QPixmap>
#include<QTextDocument>
#include<QDesktopServices>
#include "client.h"
#include "QFile"
#include "QTextStream"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include"historique.h"
#include "QFile"
#include <QTcpSocket>
#include "arduino.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->CIN->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    ui->sup->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    ui->NOM->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->PRENOM->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->NUM_TELEPHONE->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->EMAIL->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9@.]+")));

    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
         //A.write_to_arduino("0");
         A.read_from_arduino();
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label2())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
         //A.write_to_arduino("0");
         A.read_from_arduino();



   //ui->CIN->setValidator(new QIntValidator(0,999999,this));
   mCamera = new QCamera(this);
   mCameraViewfinder = new QCameraViewfinder(this);
   mCameraImageCapture = new QCameraImageCapture(mCamera, this);
   mLayout = new QVBoxLayout;
   mOptionsMenu = new QMenu ("Options", this);
   mAllumerAction = new QAction("Allumer", this);
   mEteindreAction = new QAction("Eteindre", this);
   mCaptureAction = new QAction("Capturer", this);

   mOptionsMenu->addActions({mAllumerAction, mEteindreAction, mCaptureAction});

   ui->optionspushButton_8->setMenu(mOptionsMenu);
   mCamera->setViewfinder(mCameraViewfinder);
   mLayout->addWidget(mCameraViewfinder);
   mLayout->setMargin(0);
   ui->scrollArea->setLayout(mLayout);

   connect(mAllumerAction, &QAction::triggered, [&]()
   {
       mCamera ->start();
   });
   connect(mEteindreAction, &QAction::triggered, [&]()
   {
       mCamera ->stop();
   });
   connect(mCaptureAction, &QAction::triggered, [&]()
   {
       auto filename = QFileDialog::getSaveFileName(this, "Capturer","/",
                                                    "Image(*.jpg;*.jpeg)" );
       if (filename.isEmpty()){return ;}
       mCameraImageCapture->setCaptureDestination(
                   QCameraImageCapture::CaptureToFile);
       QImageEncoderSettings imageEncadorSettings;
       imageEncadorSettings.setCodec("image/jpeg");
       imageEncadorSettings.setResolution(1600,1200);
       mCameraImageCapture->setEncodingSettings(imageEncadorSettings);
       mCamera->setCaptureMode(QCamera::CaptureStillImage);
       mCamera->start();
       mCamera->searchAndLock();
       mCameraImageCapture->capture(filename);
       mCamera->unlock();

   });
   mOptionsMenuTrier = new QMenu ("Options", this);
   mTrierCINAsccAction = new QAction("Trier par CIN ASC", this);
   mTrierCINDescAction = new QAction("Trier par CIN DESC", this);
   mTrierNomAction = new QAction("Trier par Nom", this);

   ui->pushButton_7->setMenu(mOptionsMenuTrier);
   mOptionsMenuTrier->addActions({mTrierCINDescAction, mTrierCINAsccAction, mTrierNomAction});
   connect(mTrierCINAsccAction, &QAction::triggered, [&]()
   {
       ui->tableView->setModel(c->afficherTriCINAsc());

   }
  );
   connect(mTrierCINDescAction, &QAction::triggered, [&]()
   {
      ui->tableView->setModel(c->afficherTriCINDesc());
   });
   connect(mTrierNomAction, &QAction::triggered, [&]()
   {
       ui->tableView->setModel(c->afficherTriNOM());

       });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//modifierh
{
    int CIN =ui->CIN->text().toInt();
    QString NOM = ui->NOM->text();
    QString PRENOM = ui->PRENOM->text();
    QString NUM_TELEPHONE = ui->NUM_TELEPHONE->text();
    bool test=c->modifierj(ui->CIN->text().toInt(),ui->NOM->text(),ui->PRENOM->text(),ui->NUM_TELEPHONE->text(),ui->EMAIL->text());
    ui->tableView->setModel(c->afficher());//MISE AJOUR
    ui->CIN->clear();
    ui->NOM->clear();
    ui->PRENOM->clear();
    ui->NUM_TELEPHONE->clear();
    ui->EMAIL->clear();
        if (test)
              {


                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);}//ui->tableView->setModel(c->trie());
        Historique h;

        h.save1("NOM:"+ui->NOM->text(),"PRENOM :"+ui->PRENOM->text(),"NUM-TELEPHONE:"+ui->NUM_TELEPHONE->text(),
                "EMAIL:"+ui->EMAIL->text());
}


void MainWindow::on_pushButton_4_clicked()
{
    Historique h;
    h.load();
    h.load();
    QString link="C:/Users/LENOVO/Documents/interfaceClientsansArd/Historique.txt";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_2_clicked()
{
    int CIN=ui->CIN->text().toInt();
    QString NOM=ui->NOM->text();
    QString PRENOM=ui->PRENOM->text();
    QString NUM_TELEPHONE=ui->NUM_TELEPHONE->text();

    QString EMAIL(ui->EMAIL->text());
  QString CIN1=ui->CIN->text();

     client c(CIN,NOM,PRENOM,NUM_TELEPHONE,EMAIL);

bool test=c.ajouter();
ui->tableView->setModel(c.afficher());//MISE AJOUR
ui->CIN->clear();
ui->NOM->clear();
ui->PRENOM->clear();
ui->NUM_TELEPHONE->clear();
ui->EMAIL->clear();

if(test)

        QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Ajout avec succes\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_5_clicked()
{
    client c1; c1.setCIN(ui->sup->text().toInt());
    bool test=c1.supprimer(c1.getCIN());
    QString CIN1=ui->CIN->text();

    ui->tableView->setModel(c->afficher());
    ui->sup->clear();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
    }
    else
          msgBox.setText("echec d'ajout");
                msgBox.exec();
                Historique h;
                         h.save2("CIN:"+ui->sup->text());

}
void MainWindow::on_pushButton_7_clicked()
{

}


void MainWindow::on_optionspushButton_8_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{
    c->VenteFlash();
}




void MainWindow::on_Chatbox_clicked()
{
    widget =new Widget (this);
    widget->show();
}

void MainWindow::on_ok_clicked()
{
    QString review_arduino=ui->review_arduino->text();
    if (review_arduino=="1")
        A.write_to_arduino("1");
    else if (review_arduino=="2")
        A.write_to_arduino("2");
    else if (review_arduino=="3")
        A.write_to_arduino("3");
    else if (review_arduino=="4")
        A.write_to_arduino("4");
    else if (review_arduino=="5")
        A.write_to_arduino("5");
}
