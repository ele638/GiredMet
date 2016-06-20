#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVector>

    bool db_connect();
    bool db_init();
    void db_add(double value1, double value2);
    void db_exec();
    void db_update(int index, QString name, double value);
    QVector<double> db_get_all_w();
    QVector<double> db_get_all_R();
    QVector< QVector<double> > db_get_all_epsJm();
    QVector< QVector<double> > db_get_all_W_R();
    void db_close();

#endif // DATABASE_H
