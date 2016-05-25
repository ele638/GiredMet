#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVector>

    bool db_connect();
    bool db_init();
    void db_add(QString name, double value);
    void db_add(QString name1, double value1, QString name2, double value2);
    void db_update(int index, QString name, double value);
    QVector<double> db_get_all_w();
    QVector<double> db_get_all_R();
    QVector< QVector<double> > db_get_all_epsJm();
    void db_close();

#endif // DATABASE_H
