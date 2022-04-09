#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Commande::afficher());
    ui->UdateRecupEdit->setVisible(false);
    ui->UnbArSpin->setVisible(false);
    ui->etatComboBox->setVisible(false);
    ui->UprixSpin->setVisible(false);
    ui->UdateRecupEdit->setMinimumDate(QDate::currentDate());
    ui->dateRecupEdit->setMinimumDate(QDate::currentDate());
    ui->DclIdLabel->setVisible(false);
    ui->DclIdEdit->setVisible(false);
    ui->cinEdit->setValidator(cinV);
    ui->DclIdEdit->setValidator(clIDV);
    ui->idEdit->setValidator(idV);
}


MainWindow::~MainWindow()
{
    delete ui;
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

        ui->tableView->setModel(Commande::afficher());

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
    bool suppSucces= Commande::supprimer(ID);
    if(suppSucces)
    {
       ui->tableView->setModel(Commande::afficher());
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
    numChecked--;
    break;
    case 2:
    ui->UdateRecupEdit->setVisible(true);
    numChecked++;
    }
}


void MainWindow::on_UnbArCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->UnbArSpin->setVisible(false);
    numChecked--;
    break;
    case 2:
    ui->UnbArSpin->setVisible(true);
    numChecked++;
    }
}


void MainWindow::on_etatCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->etatComboBox->setVisible(false);
    numChecked--;
    break;
    case 2:
    ui->etatComboBox->setVisible(true);
    numChecked++;
    }
}


void MainWindow::on_UprixCheck_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
    ui->UprixSpin->setVisible(false);
    numChecked--;
    break;
    case 2:
    ui->UprixSpin->setVisible(true);
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
    if (now  == ui->boutonModifier)
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

            }

            if(UnbAr!=0)
            {
                C.set_nbArticles(UnbAr);
                succesModif=(succesModif&&(C.modifier(1)));
            }

            if(Uetat!=invalid)
            {
                C.set_etat(Uetat);
                succesModif=(succesModif&&(C.modifier(2)));
            }

            if(Uprix!=0)
            {
                C.set_prix(Uprix);
                succesModif =(succesModif&&(C.modifier(3)));
            }

            if (succesModif==1)
            {

                ui->tableView->setModel(Commande::afficher());

                QMessageBox::information(nullptr, QObject::tr("Table commande mise à jour"),
                            QObject::tr("Modification réussie.\n"
                                        "Appuyez sur Ok pour quitter."), QMessageBox::Ok);
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
        ui->DclIdLabel->setVisible(false);
        ui->DclIdEdit->setVisible(false);
        break;
    case 2:
        ui->DclIdLabel->setVisible(true);
        ui->DclIdEdit->setVisible(true);
    }
}


void MainWindow::on_DclIdEdit_editingFinished()
{
    ui->boutonSupprimer->setEnabled(true);
}
