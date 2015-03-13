#include "validateexp.h"

#include <QDebug>
validateExp::validateExp()
{
}


QString validateExp::validate(QString exp, QList<double> constraints)
{
    QString result;
    QStringList splitExp = exp.split(",");

    int e1Mode = splitExp[0].toInt();
    int e2Mode = splitExp[5].toInt();
    QString e1Result = validateElectrode(e1Mode,splitExp[1],splitExp[2],splitExp[3],splitExp[4], constraints);
    QString e2Result = validateElectrode(e2Mode,splitExp[6],splitExp[7],splitExp[8],splitExp[9], constraints);

    result  = e1Result + ";" + e2Result;
    return result;
}


QString validateExp::validateElectrode(int mode, QString d1, QString d2, QString d3, QString d4, QList<double> constraints)
{
    switch (mode){
    case 1:
    {
        if(d1.isEmpty() || d2.isEmpty() || d3.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() >= constraints.at(0)) return "Error: Please specify legal values to Anode Potential which is less than " + QString::number(constraints.at(0)) + ".";
        if(d2.toDouble() <= 0) return "Error: Please specify positive values to Duration.";
        if(d2.toDouble() > constraints.at(1)) return "Error: Please specify legal values to Duration which is less than " + QString::number(constraints.at(1)) + ".";
        if(d3.toDouble() <= 0) return "Error: Please specify positive values to Time Interval.";
        if(d3.toDouble() > constraints.at(2)) return "Error: Please specify legal values to Time Interval which is less than " + QString::number(constraints.at(2)) + ".";

        break;
    }
    case 2:
    {
        if(d1.isEmpty() || d2.isEmpty() || d3.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() <= 0) return "Error: Please specify positive values to Scan Rate.";
        if(d1.toDouble() >= constraints.at(3)) return "Error: Please specify legal values to Scan Rate which is less than " + QString::number(constraints.at(3)) + ".";
        if(d2.toDouble() > constraints.at(4)) return "Error: Please specify legal values to Max Anode which is less than " + QString::number(constraints.at(4)) + ".";
        if(d3.toDouble() < constraints.at(5)) return "Error: Please specify legal values to Min Anode which is greater than " + QString::number(constraints.at(5)) + ".";
        break;
    }
    case 3:
    {
        if(d1.isEmpty() || d2.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() <= 0) return "Error: Please specify positive values to Duration.";
        if(d1.toDouble() >constraints.at(10)) return"Error: Please specify legal values to Duration which is less than " + QString::number(constraints.at(10)) + ".";
        if(d2.toDouble() <= 0) return "Error: Please specify positive values to Time Interval.";
        if(d2.toDouble() >constraints.at(11)) return"Error: Please specify legal values to Time Interval which is less than " + QString::number(constraints.at(11)) + ".";
        break;
    }
    case 4:
    {
        if(d1.isEmpty() || d2.isEmpty()||d3.isEmpty() || d4.isEmpty()) return "Error: Please fill in all necessary parameters.";
        if(d1.toDouble() <= 0) return "Error: Please specify positive values to Scan Rate.";
        if(d3.toDouble() <= 0) return "Error: Please specify positive values to # of Cycles.";

        if(d1.toDouble() > constraints.at(6)) return "Error: Please specify legal values to Scan Rate which is less than " + QString::number(constraints.at(6)) + ".";
        if(d2.toDouble() > constraints.at(7)) return "Error: Please specify legal values to Max Anode which is less than " + QString::number(constraints.at(7)) + ".";
        if(d3.toDouble() > constraints.at(8)) return "Error: Please specify legal values to # of Cycles which is less than " + QString::number(constraints.at(8)) + ".";
        if(d4.toDouble() < constraints.at(9)) return "Error: Please specify legal values to Min Anode which is greater than " + QString::number(constraints.at(9)) + ".";

        break;
    }
    default:break;
    }
    return "Y";
}
