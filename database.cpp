#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QVector>

QSqlDatabase db;

// пробный метод подключения БД, неработоспособно вне моего компа
bool db_init(bool psql){
     if(psql){
         db = QSqlDatabase::addDatabase("QPSQL");
         db.setHostName("other");
         db.setDatabaseName("postgres");
         db.setUserName("postgres");
         db.setPassword("postgres");
     }else{
         db = QSqlDatabase::addDatabase("QSQLITE");
         db.setDatabaseName(qApp->applicationDirPath()+"mydb.db");
     }
     if(!db.open()){
         db.close();
         qDebug("База не подключена");
         return false;
     }else{
         QSqlQuery query(db);
         if (query.exec("DROP TABLE IF EXISTS calc")) qDebug("DROP TABLE exec");
         if (query.exec("CREATE TABLE calc (id serial PRIMARY KEY, r double precision, w double precision)")) qDebug("CREATE TABLE exec");
         query.clear();
         qDebug("База подключена");
         return true;
     }
}

// метод вставки элемента по имени поля
void db_add(QString name, double value){
    QSqlQuery query(db);

    if(query.exec("INSERT INTO calc ("+name+") VALUES ("+QString::number(value)+")")){
        qDebug("INSERT exec");
    }
    else{
        qDebug() << query.lastError().text();
    }
    query.clear();
}

// перегрузка метода для двух полей
void db_add(QString name1, double value1, QString name2, double value2){
    QSqlQuery query(db);
    if(value1 && value2 &&  query.exec( "INSERT INTO calc ("+name1+","+name2+") VALUES ("+ QString::number(value1,'g',10)+ ","+ QString::number(value2,'g',10)+ ")")) {
    }
    else{
        qDebug() << query.lastError().text();
    }
    query.clear();
}

QVector <QVector <double> > db_get_all(QString name1, QString name2){
    QSqlQuery query(db);
    QVector <QVector <double> > out;
    QVector<double> x;
    QVector<double> y;
    if(query.exec("SELECT "+name1+","+name2+" FROM calc")) {
        query.next();
        for(int i=0; i<query.size(); i++){
           if(!query.value(0).isNull()){
               x.push_back(query.value(0).toDouble(0));
               y.push_back(query.value(1).toDouble(0));
               qDebug() << "SELECT VALUE";
           }
           query.next();
        }
        out.push_back(x);
        out.push_back(y);
        qDebug() << out.size();
        return out;
    }
    else{
        qDebug() << query.lastError().text();
    }
    query.clear();
    return out;
}

void db_close(){
    db.close();
    if(!db.isOpen()) qDebug() << "Database disconnected";

}
