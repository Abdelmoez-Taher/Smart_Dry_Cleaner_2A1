#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "commande.h"
#include <QIntValidator>
#include <QDoubleValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_boutonAjouter_clicked();

    void on_boutonSupprimer_clicked();

    void on_UdateRecupCheck_stateChanged(int arg1);

    void on_UnbArCheck_stateChanged(int arg1);

    void on_etatCheck_stateChanged(int arg1);

    void on_UprixCheck_stateChanged(int arg1);

    void on_UdateRecupEdit_editingFinished();

    void on_UnbArSpin_editingFinished();

    void on_UprixSpin_editingFinished();

    void on_etatComboBox_currentIndexChanged(int index);

    void focusChanged(QWidget* old,QWidget* now);


    void on_DconfirmCheck_stateChanged(int arg1);

    void on_DclIdEdit_editingFinished();

private:
    Ui::MainWindow *ui;

    Commande Ctemp;
    int numChecked=0 , numEdited=0, UnbAr=0 ;
    float Uprix=0;
    QString UdateRecup="";
    state Uetat=invalid;
    bool DconfirmBool=false;
    QValidator * cinV = new QIntValidator(0, 99999999, this);
    //QValidator * prixV = new QDoubleValidator(5.0 , 10000.0, 3, this);
    QValidator * clIDV = new QIntValidator(0, 999, this);
    QValidator * idV = new QIntValidator(0, 50000, this);
};
#endif // MAINWINDOW_H
