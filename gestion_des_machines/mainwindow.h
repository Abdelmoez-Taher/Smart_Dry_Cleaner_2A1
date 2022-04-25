#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"machines.h"
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
    void on_pushButton_clicked();

    void on_le_ajouter_clicked();
    void on_le_modifier_clicked();

    void on_le_supprimer_clicked();

    void on_le_trier_clicked();
    void on_le_recherche_clicked();





    void on_le_pdf_clicked();

    void on_le_connexion_web_clicked();

private:
    Ui::MainWindow *ui;
    Machines M;
};
#endif // MAINWINDOW_H
