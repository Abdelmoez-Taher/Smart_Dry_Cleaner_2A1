#include "connection.h"

Connection::Connection(){}

bool Connection::createConnect()
{
db = QSqlDatabase::addDatabase("QODBC");   //instance de la classe QSqlDatabase, dont les méthodes permettent de donner les paramètres d'accès à la BD
bool test=false;
db.setDatabaseName("Source_TeClean");
db.setUserName("moez");//inserer nom de l'utilisateur
db.setPassword("moez");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

return  test;
}

void Connection::closeConnect(){db.close();}
