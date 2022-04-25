#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
Connection::Connection()
{

}

bool Connection::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A1");
db.setUserName("SYSTEM");//inserer nom de l'utilisateur
db.setPassword("khadija");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
