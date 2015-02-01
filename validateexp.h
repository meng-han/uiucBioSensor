#ifndef VALIDATEEXP_H
#define VALIDATEEXP_H

#include <QString>
#include <QStringList>

class validateExp
{
public:
    validateExp();
    QString validate(QString);
    QString validateElectrode(int mode, QString d1, QString d2, QString d3);

};

#endif // VALIDATEEXP_H
