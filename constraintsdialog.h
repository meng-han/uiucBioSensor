#ifndef CONSTRAINTSDIALOG_H
#define CONSTRAINTSDIALOG_H

#include <QDialog>

namespace Ui {
class constraintsDialog;
}

class constraintsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit constraintsDialog(QWidget *parent = 0);
    ~constraintsDialog();
    double spCon1;
    int spCon2;
    int spCon3;
    int lsvCon1;
    double lsvCon2;
    double lsvCon3;
    int lscvCon1;
    double lscvCon2;
    int lscvCon3;
    double lscvCon4;
    int ocvCon1;
    int ocvCon2;
    void loadAllConstraints();


private slots:
    void on_buttonBox_accepted();
    void assignAllConstraints();
    void setConstraintsLineEdits();

private:
    Ui::constraintsDialog *ui;

    bool firstTime = true;

};

#endif // CONSTRAINTSDIALOG_H
