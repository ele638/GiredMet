#include <QtSql>
#include <QMessageBox>

// пробный метод подключения БД, неработоспособно вне моего компа
void init(){
     QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("localhost");
     db.setDatabaseName("ele638");
     db.setUserName("ele638");
     db.setPassword("******");
     db.open();
     QSqlQuery query("", db);
     query.exec("insert into country values ('paris',1)");
     query.exec("select name from country limit 1");
     QMessageBox msg;
     query.next();
     msg.setText(query.value(0).toString());
     msg.exec();
     db.close();
}
