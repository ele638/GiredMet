#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QVector>

QSqlDatabase db;

// пробный метод подключения БД, неработоспособно вне моего компа
bool db_connect(bool psql){
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
     }
     qDebug("База подключена");
     return true;
}

bool db_init(){
        QSqlQuery query(db);
        if (query.exec("DROP TABLE IF EXISTS calc")) qDebug("DROP TABLE exec");
        if (query.exec("CREATE TABLE calc "
                       "(id serial PRIMARY KEY, "
                        "r double precision, "
                        "w double precision, "
                        "tetha double precision, "
                        "n double precision, "
                        "k double precision, "
                        "eps1 double precision, "
                        "eps2 double precision, "
                        "epsJm double precision)")) qDebug("CREATE TABLE exec");
        query.finish();
        qDebug("База пересоздана");
        return true;
}

// метод вставки элемента по имени поля
void db_add(QString name, double value){
    QSqlQuery query(db);
    if(!query.exec("INSERT INTO calc ("+name+") VALUES ("+QString::number(value)+")")){
        qDebug() << query.lastError().text();
    }
    query.clear();
}


// перегрузка метода для двух полей
void db_add(QString name1, double value1, QString name2, double value2){
    QSqlQuery query(db);
    if(!value1 || !value2 || !query.exec( "INSERT INTO calc ("+name1+","+name2+") VALUES ("+ QString::number(value1,'g',10)+ ","+ QString::number(value2,'g',10)+ ")")){
        qDebug() << query.lastError().text();
    }
    query.clear();
}

void db_update(int index, QString name, double value){
    QSqlQuery query(db);
    if(!query.exec("UPDATE calc SET " + name + " = " + QString::number(value, 'g', 10) + " WHERE id = " + QString::number(index))){
        qDebug() << query.lastError().text();
    }
    query.clear();
}

QVector<double> db_get_all_w(){
    QSqlQuery query(db);
    QVector<double> array;
    try{
        query.exec("SELECT w FROM calc");
        while(query.next()){
            array.append(query.value(0).toDouble());
        }
        return array;
    }catch (QException e){
        qDebug() << "ERROR IN get_all_w !" << query.lastError();
    }
    return array;
}

QVector<double> db_get_all_R(){
    QSqlQuery query(db);
    QVector<double> array;
    try{
        query.exec("SELECT r FROM calc");
        while(query.next()){
            array.append(query.value(0).toDouble());
        }
        return array;
    }catch (QException e){
        qDebug() << "ERROR IN get_all_R !" << query.lastError();
    }
    return array;
}

QVector< QVector<double> > db_get_all_epsJm(){
    QSqlQuery query(db);
    QVector<double> r, espjm;
    QVector< QVector<double> > array;
    try{
        query.exec("SELECT r, epsjm FROM calc ORDER BY r ASC");
        while(query.next()){
            r.append(query.value(0).toDouble());
            espjm.append(query.value(1).toDouble());
        }
        array.append(r);
        array.append(espjm);
        return array;
    }catch (QException e){
        qDebug() << "ERROR IN db_get_all_espJm !" << query.lastError();
    }
    return array;
}

void db_close(){
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(db.connectionName());
    if(!db.isOpen()) qDebug() << "База отключена";
}
