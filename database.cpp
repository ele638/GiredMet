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
         db.setHostName("localhost");
         db.setDatabaseName("ele638");
         db.setUserName("ele638");
         db.setPassword("alpine");
     }else{
         db = QSqlDatabase::addDatabase("QSQLITE");
         db.setDatabaseName(QDir::currentPath()+"/mydb.db");
     }
     if(!db.open()){
         db.close();
         db = QSqlDatabase();
         QSqlDatabase::removeDatabase(db.connectionName());
         qDebug("База не подключена");
         return false;
     }else{
         QSqlQuery query(db);
         if (query.exec("DROP TABLE IF EXISTS calc")) qDebug("DROP TABLE exec");
         if (query.exec("CREATE TABLE calc (id serial PRIMARY KEY, r double precision, w double precision)")) qDebug("CREATE TABLE exec");
         query.finish();
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
        for(int i=0; query.next(); i++){
           try{
               x.push_back(query.value(0).toDouble(0));
               y.push_back(query.value(1).toDouble(0));
           }catch(QException e){
                qDebug() << query.lastError() << "index: " << i;
           }
           query.next();
        }
        out.push_back(x);
        out.push_back(y);
        return out;
    }
    else{
        qDebug() << query.lastError().text();
    }
    query.clear();
    return out;
}

double get_R(double w){
    QSqlQuery query(db);
    try{
        query.exec("SELECT r FROM calc WHERE w="+ QString::number(w));
        query.next();
        if(query.isValid())
        {
            qDebug() << "GOT" << w;
            return query.value(0).toDouble();
        }
        else{
            //qDebug() << "Error in value " << w;
        }
    }catch (QException e){
        qDebug() << "ERROR IN get_R !" << query.lastError();
    }
    return NULL;
}

QVector<double> get_all_w(){
    QSqlQuery query(db);
    QVector<double> array;
    try{
        query.exec("SELECT w FROM calc ORDER BY w ASC");
        while(query.next()){
            array.append(query.value(0).toDouble());
        }
        return array;
    }catch (QException e){
        qDebug() << "ERROR IN get_all_w !" << query.lastError();
    }
    return array;
}

QVector<double> get_all_R(){
    QSqlQuery query(db);
    QVector<double> array;
    try{
        query.exec("SELECT r FROM calc ORDER BY r ASC");
        while(query.next()){
            array.append(query.value(0).toDouble());
        }
        return array;
    }catch (QException e){
        qDebug() << "ERROR IN get_all_R !" << query.lastError();
    }
    return array;
}

void db_close(){
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(db.connectionName());
    if(!db.isOpen()) qDebug() << "База отключена";
}
