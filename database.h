#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVector>

    bool db_init(bool psql);
    void db_add(QString name, double value);
    void db_add(QString name1, double value1, QString name2, double value2);
    QVector <QVector <double> > db_get_all(QString name1, QString name2);
    void db_close();

#endif // DATABASE_H
