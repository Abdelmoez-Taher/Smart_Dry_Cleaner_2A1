#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "historique.h"
#include "arduino.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tabperso_3->setModel(tmpperso.afficher());
    ui->comboBox_5->setModel(tmpperso.afficher());
    ui->cin_10->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->numtel_3->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->le_id->setValidator(new QIntValidator (0, 99999999, this));
    ui->tab_machine->setModel(M.afficher());

    ui->tabproduit_2->setModel(tmpproduit.afficher());//refresh
    ui->comboBox_ID_produit_modifier_2->setModel(tmpproduit.afficherId());
    ui->tableView->setModel(M.afficher());//MISE AJOUR

    ui->tableViewCommande->setModel(Commande::afficher());
    ui->UdateRecupEdit->setVisible(false);
    ui->UnbArSpin->setVisible(false);
    ui->etatComboBox->setVisible(false);
    ui->UprixSpin->setVisible(false);
    ui->UdateRecupEdit->setMinimumDate(QDate::currentDate());
    ui->dateRecupEdit->setMinimumDate(QDate::currentDate());
    ui->DcinLabel->setVisible(false);
    ui->DcinEdit->setVisible(false);
    ui->cinEdit->setValidator(cinV);
    ui->DcinEdit->setValidator(cinV);
    ui->idEdit->setValidator(idV);
    ui->manipStacked->setCurrentIndex(0);
    // REMOVE THIS
    //ui->boutonModifier->setDisabled(true);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(handleInput()));  // permet de lancer
     //le slot suite à la reception du signal readyRead (reception des données).
     QTimer *timer = new QTimer(this);
     QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onsortiev()));
     QTime now=QTime::currentTime();
     timer->start(now.msecsTo(Pointage::sortiev));
     // Gestion des clients
     ui->CIN->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
     ui->sup->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
     ui->NOM->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
     ui->PRENOM->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
     ui->NUM_TELEPHONE->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
     ui->EMAIL->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9@.]+")));

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

    ui->pushButton_11->setMenu(mOptionsMenuTrier);
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
void MainWindow::update_label()
{
    data=A.read_from_arduino();
    QString DataAsString = QString(data);
    qDebug()<< data;

     ui->label_95->setText(data);

}


void MainWindow::on_boutonAjouter_clicked()
{
     //obtenir ID_Employe de l'authentification

    int CIN=ui->cinEdit->text().toInt();
    int nbArticles=ui->nbArSpin->value();
    double prix=ui->prixSpin->value();
    QString dateRecuperation=ui->dateRecupEdit->date().toString("dd/MM/yyyy");
    Commande C(nbArticles, CIN, prix, dateRecuperation);
    bool succesAjout=C.ajouter();

    if (succesAjout)
    {

        ui->tableViewCommande->setModel(Commande::afficher());

        QMessageBox::information(nullptr, QObject::tr("Table commande mise à jour"),
                    QObject::tr("Ajout réussi.\n"
                                "Appuyez sur Ok pour quitter."), QMessageBox::Ok);
    }
    else
        QMessageBox::warning(nullptr, QObject::tr("Table commande inchangée"),
                    QObject::tr("Ajout échoué.\n"
                                "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);
}


void MainWindow::on_boutonSupprimer_clicked()
{
    int ID=ui->idEdit->text().toInt();
    //Check CIN in database
    bool suppSucces= Commande::supprimer(ID);
    if(suppSucces)
    {
       ui->tableViewCommande->setModel(Commande::afficher());
       QMessageBox::information(nullptr, QObject::tr("Table commande mise à jour"),
                   QObject::tr("Suppression réussie.\n"
                               "Appuyez sur Ok pour quitter."), QMessageBox::Ok);
    }
    else
        QMessageBox::warning(nullptr, QObject::tr("Table commande inchangée"),
                    QObject::tr("Suppression échouée.\n"
                                "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);
}


void MainWindow::on_UdateRecupCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->UdateRecupEdit->setVisible(false);
    if (numChecked == 1)
    {
        ui->boutonModifier->setEnabled(false);
    }
    numChecked--;
    UdateRecup="";
    break;
    case 2:
    ui->UdateRecupEdit->setVisible(true);
    if (numChecked==0)
    {
    ui->boutonModifier->setEnabled(true);
    }
    numChecked++;
    }
}


void MainWindow::on_UnbArCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->UnbArSpin->setVisible(false);
    if (numChecked == 1)
    {
        ui->boutonModifier->setEnabled(false);
    }
    numChecked--;
    UnbAr=0;
    break;
    case 2:
    ui->UnbArSpin->setVisible(true);
    if (numChecked==0)
    {
    ui->boutonModifier->setEnabled(true);
    }
    numChecked++;
    }
}


void MainWindow::on_etatCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->etatComboBox->setVisible(false);
    if (numChecked == 1)
    {
        ui->boutonModifier->setEnabled(false);
    }
    numChecked--;
    Uetat=invalid;
    break;
    case 2:
    ui->etatComboBox->setVisible(true);
    if (numChecked==0)
    {
    ui->boutonModifier->setEnabled(true);
    }
    numChecked++;
    }
}


void MainWindow::on_UprixCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->UprixSpin->setVisible(false);
    if (numChecked == 1)
    {
        ui->boutonModifier->setEnabled(false);
    }
    numChecked--;
    Uprix=0;
    break;
    case 2:
    ui->UprixSpin->setVisible(true);
    if (numChecked==0)
    {
    ui->boutonModifier->setEnabled(true);
    }
    numChecked++;
    }
}


void MainWindow::on_UdateRecupEdit_editingFinished()
{
    UdateRecup = ui->UdateRecupEdit->date().toString("dd/MM/yy");
    numEdited++;
}


void MainWindow::on_UnbArSpin_editingFinished()
{
    UnbAr=ui->UnbArSpin->value();
    numEdited++;
}


void MainWindow::on_UprixSpin_editingFinished()
{
    Uprix=ui->UprixSpin->value();
    numEdited++;
}


void MainWindow::focusChanged(QWidget* old,QWidget* now)
{
    if ((now  == ui->boutonModifier)&&(now!=old))
    {
        bool numTest=((numChecked<=numEdited)&&((numChecked*numEdited)!=0));
        if(numTest)
        {
            Commande C;
            C.set_ID(ui->idEdit->text().toInt());
            bool succesModif=true;

            if(UdateRecup!="")
            {
                C.set_dateRecuperation(UdateRecup);
                succesModif=(succesModif&&(C.modifier(0)));
                UdateRecup="";

            }

            if(UnbAr!=0)
            {
                C.set_nbArticles(UnbAr);
                succesModif=(succesModif&&(C.modifier(1)));
                UnbAr=0;
            }

            if(Uetat!=invalid)
            {
                C.set_etat(Uetat);
                succesModif=(succesModif&&(C.modifier(2)));
                Uetat=invalid;
            }

            if(Uprix!=0)
            {
                C.set_prix(Uprix);
                succesModif =(succesModif&&(C.modifier(3)));
                Uprix=0;
            }

            if (succesModif==1)
            {

                ui->tableViewCommande->setModel(Commande::afficher());

                QMessageBox::information(nullptr, QObject::tr("Table commande mise à jour"),
                            QObject::tr("Modification réussie.\n"
                                        "Appuyez sur Ok pour quitter."), QMessageBox::Ok);
                succesModif = 0;
            }
            else
                QMessageBox::warning(nullptr, QObject::tr("Table commande inchangée"),
                            QObject::tr("Modification échouée.\n"
                                        "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);

        }
        else
        {
            QString warningText="<html><head/><body><p><span style=\" color:#ff0000;\">Veuillez insérer toutes les informations à modifier!</span></p></body></html>";
            ui->fillWarning->setText(warningText);
        }
    }
}


void MainWindow::on_etatComboBox_currentIndexChanged(int index)
{
    Uetat=(state)index;
    numEdited++;
}

void MainWindow::on_DconfirmCheck_stateChanged(int arg1)
{
    switch (arg1)
    {
    case 0:
        ui->DcinLabel->setVisible(false);
        ui->DcinEdit->setVisible(false);
        break;
    case 2:
        ui->DcinLabel->setVisible(true);
        ui->DcinEdit->setVisible(true);
    }
}


void MainWindow::on_DcinEdit_editingFinished()
{
    if(Commande::CINValid(ui->DcinEdit->text().toLongLong()))
    {
    ui->boutonSupprimer->setEnabled(true);

    }
    else
    {
    ui->Failmsg->setText("INVALID CIN !");
    }
}

void MainWindow::on_idEdit_editingFinished()
{
    if(Commande::IDValid(ui->idEdit->text().toInt(), CManipTemp))
    {
        ui->preBoutonModifier->setEnabled(true);
        ui->preBoutonSupprimer->setEnabled(true);

    }
    else
    {
        qDebug() <<ui->idEdit->text().toInt();
        ui->idWarning->setText("<html><head/><body><p><span style=\" color:#ff0000;\">Cet ID ne correspond à aucune commande. Veuillez réessayer.</span></p></body></html>");
    }
}

void MainWindow::on_preBoutonModifier_clicked()
{
    ui->UcinRead->setText(QString::number(CManipTemp.get_CIN()));
    ui->UIdRead->setText(QString::number(CManipTemp.get_ID()));
    ui->UdateDepotRead->setDate(QDate::fromString(CManipTemp.get_dateDepot(), "dd/MM/yyyy"));
    ui->UdateRecupRead->setDate(QDate::fromString(CManipTemp.get_dateRecuperation(), "dd/MM/yyyy"));
    ui->UnbArRead->setValue(CManipTemp.get_nbArticles());
    ui->UetatRead->setCurrentIndex(CManipTemp.get_etat());
    ui->UprixRead->setValue(CManipTemp.get_prix());
    ui->manipStacked->setCurrentIndex(1);

}

void MainWindow::on_preBoutonSupprimer_clicked()
{
    ui->DIdRead->setText(QString::number(CManipTemp.get_ID()));
    ui->DdateDepotRead->setDate(QDate::fromString(CManipTemp.get_dateDepot(), "dd/MM/yyyy"));
    ui->DdateRecupRead->setDate(QDate::fromString(CManipTemp.get_dateRecuperation(), "dd/MM/yyyy"));
    ui->DnbArRead->setValue(CManipTemp.get_nbArticles());
    ui->DetatRead->setCurrentIndex(CManipTemp.get_etat());
    ui->DprixRead->setValue(CManipTemp.get_prix());
    ui->manipStacked->setCurrentIndex(2);
}



void MainWindow::on_boutonAnnulerSupp_clicked()
{
    ui->manipStacked->setCurrentIndex(0);
}

void MainWindow::on_boutonAnnulerModif_clicked()
{
    ui->manipStacked->setCurrentIndex(0);
}


void MainWindow::handleInput()
{
    //data=A.read_from_arduino();
    line=A.read_line_from_arduino();
    //qDebug()<<"this is line, the std::string"<<line;
    //std::string temp=data.toStdString();
    //qDebug()<<"standard string converted from data called temp:"<< &temp;

   std::cout<<"this is the c++ string"<<line;

    myData=QString::fromStdString(line);
    myData.chop(2);
    qDebug()<<"this is myData which contains anything as a qstring"<<myData;
   /* if(myData=="0") //carte détectée

        ui->detectLabel->setText("Carte détectée");

    else if (myData=="1") //numéro carte correspond à employé
        {
        int ID_Employe=Pointage::IDEmfromRFID(RFID);
        //Pointage p(ID_Employe);
        int testPointage=Pointage::pointageValid(ID_Employe);
        switch(testPointage)
        {
        case -1:         //pas de pointage
        {

            if(QTime::currentTime() < Pointage::entreev.addSecs(-5*60)) //pointage entree avant 7h55
                {
                    ui->messageLabel->setText("Merci pour votre assiduité Revenez à 8h");
                    A.write_to_arduino("0");
                }
            else if((QTime::currentTime() >= Pointage::entreev.addSecs(-5*60)) && (QTime::currentTime() <= Pointage::entreev.addSecs(9*60*60)) ) //pointage entree entre 7h55 et 14h
                {
                Pointage p(ID_Employe);
                p.ajouter();
                ui->messageLabel->setText("Bienvenu!");
                A.write_to_arduino("1");
                }
            else //pointage entree après 14h00
                {
                Pointage p(ID_Employe);
                p.ajouter();
                ui->messageLabel->setText("Accès refusé. Veuillez contacter votre manager!");
                A.write_to_arduino("0");
                }
            break;
        }
        case 0:         //pas de sortie
        {
            int assiduite=Pointage::AssidfromPKey(ID_Employe);
            Pointage p(ID_Employe, QTime::currentTime(), assiduite);
            p.modifier();
            ui->messageLabel->setText("Au revoir! Reposez-vous bien!");
            A.write_to_arduino("1");

            break;
        }
        case 1:         //sortie
            ui->messageLabel->setText("Accès refusé, votre shift est terminé. Revenez le jour suivant ou contactez votre géant!");
            A.write_to_arduino("0");
            break;
        }
    }
    else if(myData=="-1") //carte ne correspond pas à employé
    {
        ui->messageLabel->setText("La carte introduite ne correspond à aucun des employés!");
    }
        else
    {
        //ui->detectLabel->setText("Carte détectée");*/
        if(myData=="-1") //carte ne correspond pas à employé
        {
            ui->detectLabel->setText("Carte détectée");
            ui->messageLabel->setText("La carte introduite ne correspond à aucun des employés!");
            A.write_to_arduino("0");
        }
            else
        {
            int indice=myData.toInt();
            RFID=Pointage::RFID[indice];
        QString SRFID=QString::number(RFID);
        ui->detectLabel->setText("Carte détectée");
        ui->numCarteLabel->setText("Le numéro de la carte est: "+ SRFID);
        qDebug()<<"this is SRFID which contains RFID as a qstring"<<SRFID;
        if (Pointage::checkAccess(RFID))
        {
            int ID_Employe=Pointage::IDEmfromRFID(RFID);
            //Pointage p(ID_Employe);
            int testPointage=Pointage::pointageValid(ID_Employe);
            switch(testPointage)
            {
            case -1:         //pas de pointage
            {

                if(QTime::currentTime() < Pointage::entreev.addSecs(-5*60)) //pointage entree avant 7h55
                    {
                        ui->messageLabel->setText("Merci pour votre assiduité Revenez à 8h");
                        A.write_to_arduino("0");
                    }
                else if((QTime::currentTime() >= Pointage::entreev.addSecs(-5*60)) && (QTime::currentTime() <= Pointage::entreev.addSecs(9*60*60)) ) //pointage entree entre 7h55 et 14h
                    {
                    Pointage p(ID_Employe);
                    p.ajouter();
                    ui->messageLabel->setText("Bienvenu!");
                    A.write_to_arduino("1");
                    }
                else //pointage entree après 14h00
                    {
                    Pointage p(ID_Employe);
                    p.ajouter();
                    ui->messageLabel->setText("Accès refusé. Veuillez contacter votre manager!");
                    A.write_to_arduino("0");
                    }
                break;
            }
            case 0:         //pas de sortie
            {
                int assiduite=Pointage::AssidfromPKey(ID_Employe);
                Pointage p(ID_Employe, QTime::currentTime(), assiduite);
                p.modifier();
                ui->messageLabel->setText("Au revoir! Reposez-vous bien!");
                A.write_to_arduino("1");

                break;
            }
            case 1:         //sortie
            {
                ui->messageLabel->setText("Accès refusé, votre shift est terminé. Revenez le jour suivant ou contactez votre géant!");
                A.write_to_arduino("0");
                break;
            }
        }
        }
        else
        {
           ui->messageLabel->setText("La carte introduite ne correspond à aucun des employés!");
           A.write_to_arduino("0");
        }

   }
}

void MainWindow::onsortiev()
{
    Pointage::checkAbsence();
}



void MainWindow::on_pushButton_2_clicked()
{
    Calendrier *cal = new Calendrier();
    cal->resize(600,600);
    cal->show();
}















//void MainWindow::on_pushButton_trid_clicked()
//{
//    ui->tabperso->setModel(tmpperso.trie(0));

//}

//void MainWindow::on_tri_salaire_clicked()
//{
   //     ui->tabperso->setModel(tmpperso.trie_salaire(0));
//}





void MainWindow::on_QRcodecom_3_clicked()


{

    personnel A;

     if(ui->tabperso_3->currentIndex().row()==-1)
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




         A.setcin(ui-> cin_10 ->text());
         A.setnom(ui->nom_3 ->text());
         A.setprenom(ui->prenom_3 ->text());

         A.setdate_naissance(ui->date_naissance_3->text());

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
                                      ui->qrlabel_3->setPixmap(QPixmap::fromImage(im));
}
}
















void MainWindow::on_pushButton_25_clicked()
{
    A.write_to_arduino("1") ;

}

void MainWindow::on_mod_5_clicked()
{
    QString cin= ui->comboBox_5->currentText();
     QString adresse=ui->lineEdit_37->text();
    QString num_tel=ui->lineEdit_36->text();



  bool test=tmpperso. modifier( cin,adresse,num_tel );

     if (test)
     { //ui->comboBox->setModel(tmpperso.afficher());
         ui->tabperso_3->setModel(tmpperso.afficher());//refresh
         QMessageBox::information(nullptr, QObject::tr("Modifier un personnel"),
                     QObject::tr("Personnel modifié.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Modifier un personnel"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_supp_3_clicked()
{
    QString cin=ui->cinmod_5->text();
    if(cin=="")
    {
     QMessageBox::information(nullptr,QObject::tr("Ajouter un personnel"),QObject::tr("Merci d'écrire le CIN "),QMessageBox::Ok);
    }
     else {
       bool test=tmpperso.supprimer(cin);
           if(test)
           {ui->tabperso_3->setModel(tmpperso.afficher());

               QMessageBox::information(nullptr, QObject::tr("supprimer un personnel"),
                                        QObject::tr("personnel supprimer.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);}
           else
              QMessageBox::critical(nullptr, QObject::tr("Supprimer un personnel"),
                                   QObject::tr("Erreur !.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow::on_add_3_clicked()
{
    bool test;
       QString cin= ui->cin_10->text();
       QString nom= ui->nom_3->text();
       QString prenom= ui->prenom_3->text();
       QString date_naissance=ui->date_naissance_3->text();
       QString adresse= ui->adresse_3->text();
       QString num_tel= ui->numtel_3->text();
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

            ui->tabperso_3->setModel(tmpperso.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Ajouter un personnel"),
                              QObject::tr("personnel ajouté.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

            }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter un personnel"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pdf_3_clicked()
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

void MainWindow::on_exel_3_clicked()
{


    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                            tr("Excel Files (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tabperso_3);
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

void MainWindow::on_tabperso_3_clicked(const QModelIndex &index)
{

    QVariant cin=ui->tabperso_3->model()->data(ui->tabperso_3->model()->index(ui->tabperso_3->currentIndex().row(),0));
    QString rescin=cin.toString();
           ui->cin_10->setText(rescin);
            QVariant nom=ui->tabperso_3->model()->data(ui->tabperso_3->model()->index(ui->tabperso_3->currentIndex().row(),1));
            QString resnom=nom.toString();
            ui->nom_3->setText(resnom);
            QVariant prenom=ui->tabperso_3->model()->data(ui->tabperso_3->model()->index(ui->tabperso_3->currentIndex().row(),2));
            QString resprenom=prenom.toString();
            ui->prenom_3->setText(resprenom);
            QVariant date_naissance=ui->tabperso_3->model()->data(ui->tabperso_3->model()->index(ui->tabperso_3->currentIndex().row(),6));
            //QString resdate_naissance=date_naissance.toString();
          // ui->date_naissance->setText(resdate_naissance);
            QVariant adresse=ui->tabperso_3->model()->data(ui->tabperso_3->model()->index(ui->tabperso_3->currentIndex().row(),5));
            QString resadresse=adresse.toString();
            ui->adresse_3->setText(resadresse);
           QVariant numtel=ui->tabperso_3->model()->data(ui->tabperso_3->model()->index(ui->tabperso_3->currentIndex().row(),7));
           QString resnumtel=numtel.toString();
          ui->numtel_3->setText(resnumtel);

}

void MainWindow::on_pushButton_24_clicked()
{
    QString nom=ui->lineEdit_idch_4->text();

    ui->tabperso_3->setModel(tmpperso.chercher(nom));
}

void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_ajouter_produit_2_clicked()
{
    bool test;
        int id= ui->produitid->text().toInt();
        QString nom= ui->produitnom->text();
        float prix= ui->produitprix->text().toFloat();
        QString datee=ui->dateProduit->text();
        int qte= ui->produitQtt->text().toInt();


        if(nom==""|| id==0||nom.length()>10||qte==0||prix==0.0)


                    {
                                  QMessageBox::critical(nullptr, QObject::tr("vide"),
                                  QObject::tr("veuillez saisir tous les champs correctement!\n"), QMessageBox::Cancel);
                                  test=false;

                    }
        else{
        produit p(id,nom,prix,datee,qte);
         test=p.ajouter();}
         if(test)
         {
             ui->tabproduit_2->setModel(tmpproduit.afficher());//refresh
             QMessageBox::information(nullptr, QObject::tr("Ajouter un produit"),
                               QObject::tr("produit ajouté.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

             }
               else
                   QMessageBox::critical(nullptr, QObject::tr("Ajouter un produit"),
                               QObject::tr("Erreur !.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pushButton_10_clicked()
{
    A.write_to_arduino("0") ;
}

void MainWindow::on_pushButton_9_clicked()
{
    A.write_to_arduino("1") ;

}

void MainWindow::on_pushButton_rechercher_produit_2_clicked()
{
    int id;
    id=ui->lineEdit_14->text().toInt();
   bool test= true;
    if(test==(true))
    {
      ui->tabproduit_2->setModel(tmpproduit.rechercher(id));
}
}


void MainWindow::on_pushButton_8_clicked()
{
    QPrinter printer;

        QPrintDialog *dialog = new QPrintDialog(&printer, this);
        dialog->setWindowTitle(tr("Print Document"));
            dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
        if (dialog->exec() != QDialog::Accepted)
            return;
        QPainter painter;
        painter.begin(&printer);
        int i = 4000;
             painter.setPen(Qt::blue);
             painter.setFont(QFont("Arial", 30));
             painter.drawText(1100,1200,"Liste Des Produits ");
             painter.setPen(Qt::black);
             painter.setFont(QFont("Arial", 50));

             painter.drawRect(100,100,7300,2600);

             painter.drawRect(0,3000,9600,500);
             painter.setFont(QFont("Arial", 9));
             painter.drawText(200,3300,"ID");
             painter.drawText(1700,3300,"NOM");
             painter.drawText(3200,3300,"PRIX");
             painter.drawText(4900,3300,"DATEE");
             painter.drawText(6600,3300,"QTE");

             QSqlQuery query;
             query.prepare("select * from PRODUIT");
             query.exec();
             while (query.next())
             {
                 painter.drawText(200,i,query.value(0).toString());
                 painter.drawText(1700,i,query.value(1).toString());
                 painter.drawText(3200,i,query.value(2).toString());
                 painter.drawText(4900,i,query.value(3).toString());
                 painter.drawText(6600,i,query.value(4).toString());

                i = i + 500;
             }


             painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                                printer.paperRect().y() + printer.pageRect().height()/2);

             painter.translate(-width()/2, -height()/2);

}



void MainWindow::on_pushButton_imprimer_produit_2_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
               QPdfWriter pdf("C:/Users/AMEN/Desktop/amine/Pdf.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste Des Produits ");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 50));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"ID");
                   painter.drawText(1700,3300,"NOM");
                   painter.drawText(3200,3300,"PRIX");
                   painter.drawText(4900,3300,"DATEE");
                   painter.drawText(6600,3300,"QTE");

                   QSqlQuery query;
                   query.prepare("select * from PRODUIT");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1700,i,query.value(1).toString());
                       painter.drawText(3200,i,query.value(2).toString());
                       painter.drawText(4900,i,query.value(3).toString());
                       painter.drawText(6600,i,query.value(4).toString());

                      i = i + 500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {
                           QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/AMEN/Desktop/amine/Pdf.pdf"));
                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }

}

void MainWindow::on_pushButton_Statistique_2_clicked()
{
    /*QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from PRODUIT where PRIX < 200 ");
                        float salaire=model->rowCount();
                        model->setQuery("select * from PRODUIT where PRIX  between 200 and 1000 ");
                        float salairee=model->rowCount();
                        model->setQuery("select * from PRODUIT where PRIX>1000 ");
                        float salaireee=model->rowCount();
                        float total=salaire+salairee+salaireee;
                        QString a=QString(" Produits moins de 200DT "+QString::number((salaire*100)/total,'f',2)+"%" );
                        QString b=QString(" Produits entre 200DT et 1000DT  "+QString::number((salairee*100)/total,'f',2)+"%" );
                        QString c=QString("Produits +1000DT"+QString::number((salaireee*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,salaire);
                        series->append(b,salairee);
                        series->append(c,salaireee);
                if (salaire!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( salairee!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(salaireee!=0)
                {
                         // Add labels to rest of slices
                         QPieSlice *slice2 = series->slices().at(2);
                         //slice1->setExploded();
                         slice2->setLabelVisible();
                }
                        // Create the chart widget
                        QChart *chart = new QChart();
                        // Add data to chart with title and hide legend
                        chart->addSeries(series);
                        chart->setTitle("Pourcentage Par Duree d'e promotion'Produit des PRODUITS :Nombre Des Produits  "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->resize(1000,500);
                        chartView->show();*/
}

void MainWindow::on_pushButton_modifier_produit_2_clicked()
{
    int id= ui->comboBox_ID_produit_modifier_2->currentText().toInt();
    int qte= ui->lineEdit_22->text().toInt();

  bool test=tmpproduit.modifier( id,qte );

     if (test)
     {
         ui->comboBox_ID_produit_modifier_2->setModel(tmpproduit.afficher());
         ui->tabproduit_2->setModel(tmpproduit.afficher());//refresh
         QMessageBox::information(nullptr, QObject::tr("Modifier un produit"),
                     QObject::tr("produit modifié.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Modifier un produit"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimer_produit_2_clicked()
{
    int res1=ui->comboBox_ID_produit_2->currentText().toInt();
            bool test=tmpproduit.supprimer(res1);

            if(test)
            {
                ui->comboBox_ID_produit_2->setModel(tmpproduit.afficherId());
                ui->tabproduit_2->setModel(tmpproduit.afficher());
                QMessageBox::information(nullptr, QObject::tr("Supprimer une produit"),
                            QObject::tr("produit supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Supprimer un produit"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_radioButton_tri_ID_2_clicked()
{
    ui->tabproduit_2->setModel( tmpproduit.afficher_tri_ID());

}

void MainWindow::on_radioButton_tri_nom_2_clicked()
{
    ui->tabproduit_2->setModel( tmpproduit.afficher_tri_nom());

}

void MainWindow::on_radioButton_tri_prix_2_clicked()
{
    ui->tabproduit_2->setModel( tmpproduit.afficher_tri_prix());

}

void MainWindow::on_radioButton_tri_date_2_clicked()
{
    ui->tabproduit_2->setModel( tmpproduit.afficher_tri_date());

}

void MainWindow::on_radioButton_tri_quantite_2_clicked()
{
    ui->tabproduit_2->setModel( tmpproduit.afficher_tri_quantite());

}

void MainWindow::on_pushButton_7_clicked()
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
        Historique h;
        h.save1("CIN:"+QString::number(CIN), "NOM:"+NOM,"NUM-TELEPHONE:"+ui->NUM_TELEPHONE->text(),
                "EMAIL:"+ui->EMAIL->text());
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

void MainWindow::on_pushButton_6_clicked()
{
    int CIN =ui->CIN->text().toInt();
    QString NOM = ui->NOM->text();
    QString PRENOM = ui->PRENOM->text();
    QString NUM_TELEPHONE = ui->NUM_TELEPHONE->text();
    bool test=c->modifierj(ui->CIN->text().toInt(),ui->NOM->text(),ui->PRENOM->text(),ui->NUM_TELEPHONE->text(),ui->EMAIL->text());
    ui->tableView->setModel(c->afficher());//MISE AJOUR
    Historique h;

    h.save1("CIN:"+QString::number(CIN), "NOM:"+NOM,"NUM-TELEPHONE:"+ui->NUM_TELEPHONE->text(),
            "EMAIL:"+ui->EMAIL->text());
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

}

void MainWindow::on_Chatbox_clicked()
{
    widget =new Widget (this);
    widget->show();
}

void MainWindow::on_pushButton_13_clicked()
{
    Historique h;
    h.load();
    h.load();
    QString link="C:/Users/moezt/Desktop/2021-2022/2A(moez)/2eme semestre/Projet C++/Commande/Realisation_Implementation/GUI_Commande/Historique.txt/Historique.txt";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_12_clicked()
{

}

void MainWindow::on_pushButton_14_clicked()
{
    client c1; c1.setCIN(ui->sup->text().toInt());
    bool test=c1.supprimer(c1.getCIN());
    QString CIN1=ui->CIN->text();

    ui->tableView->setModel(c->afficher());
    Historique h;
             h.save2("CIN:"+ui->sup->text());
    ui->sup->clear();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
    }
    else
          msgBox.setText("echec de suppression");
                msgBox.exec();

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

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
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

void MainWindow::on_le_pdf_clicked()
{
    Machines m;
    m.pdf();
}

void MainWindow::on_le_trier_clicked()
{
    QString attribute = ui->attributebox->currentText();
    QString croissance = ui->croicbox->currentText();
    ui->tab_machine->setModel(M.trier(attribute,croissance));
    qDebug() << attribute << croissance;

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

void MainWindow::on_le_recherche_clicked()
{
    {
        Machines m;
             ui->tableView_2->setModel(m.recherche(ui->le_cherche->text().toInt()));
             ui->le_cherche->clear();

}
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

        ui->tab_machine->setModel(M1.afficher());

        }
}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT Ok"),
                    QObject::tr("Suppression non effecute.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_le_connexion_web_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.made-in-china.com/productdirectory.do?word=dry+cleaning+machine&file=&searchType=0&subaction=hunt&style=b&mode=and&comProvince=nolimit&order=0&isOpenCorrection=1&org=top&code=3428010000&log_from=1", QUrl::TolerantMode));

}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);

}


void MainWindow::on_searchEdit_textChanged(const QString &arg1)
{
    if(arg1.size()>1){
    ui->tableViewCommande->setModel(Ctemp.search(arg1));
    }
    else {
        ui->tableViewCommande->setModel(Ctemp.afficher());

    }
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    ui->tableViewCommande->setModel(Ctemp.TRI(index));

}

void MainWindow::on_ON_clicked()
{
       A.write_to_arduino("1") ;
}

void MainWindow::on_off_clicked()
{
     A.write_to_arduino("0") ;
}
