#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QMainWindow>
#include<QTcpSocket>
#include "widget.h"
#include "arduino.h"


namespace Ui {
class MainWindow;
}
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
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    QString nomemp() const;
    quint16 port() const;


private slots:

  void on_pushButton_clicked();

 void on_pushButton_4_clicked();

 void on_pushButton_2_clicked();

 void on_pushButton_5_clicked();



 void on_pushButton_7_clicked();

 void on_optionspushButton_8_clicked();



 void on_pushButton_3_clicked();




 void on_Envoyer_clicked();

 void on_Fermer_clicked();

 void on_Chatbox_clicked();

 void on_ok_clicked();

private:
    Ui::MainWindow *ui;
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
    Arduino A;
    QString mnomemp="localhost";
    quint16 mport=3333;
    QTcpSocket *mSocket;
    Widget *widget;

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
