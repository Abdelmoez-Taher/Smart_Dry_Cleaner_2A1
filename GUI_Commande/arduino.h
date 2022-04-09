#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort> //méthodes permettant l'échange de données dans une liaison série
#include <QtSerialPort/QSerialPortInfo>//informations sur les ports disponibles
#include <QDebug>

class Arduino
{
public:
    Arduino();
    int connect_arduino(); //connecter le PC à Arduino
    int close_arduino(); //fermer la connexion entre le PC et Arduino
    int write_to_arduino(QByteArray ); //envoyer des données vers Arduino
    QByteArray read_from_arduino(); //recevoir des données à partir de la carte Arduino
    QSerialPort* getserial(); //accesseur
    QString getarduino_port_name();
private:
    QSerialPort * serial; //objet rassemblant des informations (vitesse, bits de données, etc..) et des méthodes (envoi, lecture de réception,etc..) sur ce qu'est une voie série pour Arduino
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_product_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data; //données lues à partir d'Arduino
};

#endif // ARDUINO_H
