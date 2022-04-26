#include "connection.h"

connection::connection()
{

}bool connection::createconnection()
{
   db=QSqlDatabase::addDatabase("QODBC");
   bool test=false;
   db.setDatabaseName("source_projet2A");
   db.setUserName("system");
   db.setPassword("maryem");

if (db.open()) test=true;
return test;
}
