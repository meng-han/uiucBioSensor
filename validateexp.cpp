#include "validateexp.h"

#include <QDebug>
validateExp::validateExp()
{
}


QString validateExp::validate(QString exp)
{
    QString result;
    QStringList splitExp = exp.split(",");

    int e1Mode = splitExp[0].toInt();
    int e2Mode = splitExp[4].toInt();
    QString e1Result = validateElectrode(e1Mode,splitExp[1],splitExp[2],splitExp[3]);
    QString e2Result = validateElectrode(e2Mode,splitExp[5],splitExp[6],splitExp[7]);

    result  = e1Result + ";" + e2Result;
    return result;
}


QString validateExp::validateElectrode(int mode, QString d1, QString d2, QString d3)
{
    switch (mode){
    case 1:
    {
        if(d1.isEmpty() || d2.isEmpty()||d3.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() >= 0) return "Error: Please specify negative values to Anode Potential.";
        if(d2.toDouble() <= 0) return "Error: Please specify positive values to Duration.";
        if(d3.toDouble() <= 0) return "Error: Please specify positive values to Time Interval.";
        break;
    }
    case 2:
    {
        if(d1.isEmpty() || d2.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() <= 0) return "Error: Please specify positive values to Scan Rate.";
        break;
    }
    case 3:
    {
        if(d1.isEmpty() || d2.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() <= 0) return "Error: Please specify positive values to Duration.";
        if(d2.toDouble() <= 0) return "Error: Please specify positive values to Time Interval.";
        break;
    }
    case 4:
    {
        if(d1.isEmpty() || d2.isEmpty()||d3.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() <= 0) return "Error: Please specify positive values to Scan Rate.";
        if(d3.toDouble() <= 0) return "Error: Please specify positive values to # of Cycles.";
        break;
    }
    default:break;
    }
    return "Y";
}
