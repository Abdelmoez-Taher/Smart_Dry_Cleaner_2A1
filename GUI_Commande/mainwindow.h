#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "machines.h"
#include "commande.h"
#include <QIntValidator>
#include <QDoubleValidator>
#include "arduino.h"
#include "pointage.h"
#include "calendrier.h"
#include <string>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <personnel.h>
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
#include "produit.h"
#include<QSystemTrayIcon>
#include <QAxWidget>
#include <QAxObject>
#include "qrcode.hpp"
#include <iostream>
#include <fstream>
#include "exportexcelobjet.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QDateEdit>
#include <QLineEdit>
#include <QPrinter>
#include <QPrintDialog>
#include "produit.h"
#include <QDebug>
#include<QComboBox>
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
#include<QPdfWriter>
#include<QPainter>
#include "arduino.h"
#include<QDesktopServices>
#include<QUrl>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include"QSortFilterProxyModel"
#include <QPlainTextEdit>
#include <QPlainTextDocumentLayout>
#include <QTextStream>
#include "widget.h"
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
#include "client.h"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

using std::uint8_t;
#include<QDirModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString nomemp() const;
    quint16 port() const;
    int messageboxactive,alert,led;
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

    void on_DcinEdit_editingFinished();

    void on_idEdit_editingFinished();

    void on_preBoutonModifier_clicked();

    void on_preBoutonSupprimer_clicked();


    void on_boutonAnnulerSupp_clicked();

    void on_boutonAnnulerModif_clicked();

    void handleInput();

    void onsortiev();



    void on_pushButton_2_clicked();

    void on_QRcodecom_3_clicked();

    void on_pushButton_25_clicked();

    void on_mod_5_clicked();

    void on_supp_3_clicked();

    void on_add_3_clicked();

    void on_pdf_3_clicked();

    void on_exel_3_clicked();

    void on_pushButton_24_clicked();

    void on_tabperso_3_clicked(const QModelIndex &index);

    void on_pushButton_26_clicked();

    void on_pushButton_4_clicked();

        // gestion des produits

    void on_pushButton_ajouter_produit_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_rechercher_produit_2_clicked();


    void on_pushButton_8_clicked();

    void on_pushButton_imprimer_produit_2_clicked();

    void on_pushButton_Statistique_2_clicked();

    void on_pushButton_modifier_produit_2_clicked();

    void on_pushButton_supprimer_produit_2_clicked();

    void on_radioButton_tri_ID_2_clicked();

    void on_radioButton_tri_nom_2_clicked();

    void on_radioButton_tri_prix_2_clicked();

    void on_radioButton_tri_date_2_clicked();

    void on_radioButton_tri_quantite_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_Chatbox_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_ok_clicked();

    void on_pushButton_5_clicked();

    void on_le_ajouter_clicked();

    void on_le_pdf_clicked();

    void on_le_trier_clicked();

    void on_le_modifier_clicked();

    void on_le_recherche_clicked();

    void on_le_supprimer_clicked();

    void on_le_connexion_web_clicked();

    void on_pushButton_15_clicked();




    void on_searchEdit_textChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(int index);
      void update_label();

      void on_ON_clicked();

      void on_off_clicked();

private:
    Ui::MainWindow *ui;

    Commande Ctemp, CManipTemp;
    int numChecked=0 , numEdited=0, UnbAr=0;
    long long int  RFID;
    float Uprix=0;
    QString UdateRecup="";
    state Uetat=invalid;
    bool DconfirmBool=false;
    QValidator * cinV = new QIntValidator(0, 99999999, this);
    //QValidator * prixV = new QDoubleValidator(5.0 , 10000.0, 3, this);
    QValidator * idV = new QIntValidator(0, 50000, this);
    QByteArray data;
    QString myData;
    Arduino A;
    std::string line;
    personnel tmpperso;
    produit tmpproduit;
    client *c;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOptionsMenu;
    QAction *mAllumerAction;
    QAction *mEteindreAction;
    QAction *mCaptureAction;
    QMenu *mOptionsMenuTrier;
    QAction *mTrierCINDescAction;
    QAction *mTrierCINAsccAction;
    QAction *mTrierNomAction;
    QString mnomemp="localhost";
    quint16 mport=3333;
    QTcpSocket *mSocket;
    Widget *widget;
    Machines M;


};
inline QString MainWindow::nomemp() const
{
    return mnomemp;
}
inline quint16 MainWindow::port() const
{
    return mport;
}

#endif // MAINWINDOW_H
