#include "widget.h"
#include "ui_widget.h"
#include "mainwindow.h"
#include <QTcpSocket>
#include <QTextStream>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
    //connexion avec serveur
    connect(mSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(mSocket);
       auto text =T.readAll();
       ui->textEdit->append(text);
    });
    MainWindow D(this);
    mSocket->connectToHost(D.nomemp(),D.port());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Envoyer_clicked()
{
    QTextStream T(mSocket);
    T<< "khadija"<<":"<<ui->message->text(); //utilisateur
    mSocket->flush(); //envoyer le msg au serveur
    ui->message->clear();
}


void Widget::on_Fermer_clicked()
{
    this->close();

}
