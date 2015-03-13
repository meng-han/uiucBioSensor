#include "constraintsdialog.h"
#include "ui_constraintsdialog.h"

constraintsDialog::constraintsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::constraintsDialog)
{
    ui->setupUi(this);
    if(firstTime)
        this->assignAllConstraints();

    else
        this->loadAllConstraints();

    this->setConstraintsLineEdits();

}

constraintsDialog::~constraintsDialog()
{
    delete ui;
}

void constraintsDialog::loadAllConstraints()
{
    ui->spCon1->setText(QString::number(this->spCon1));
    ui->spCon2->setText(QString::number(this->spCon2));
    ui->spCon3->setText(QString::number(this->spCon3));

    ui->lsvCon1->setText(QString::number(this->lsvCon1));
    ui->lsvCon2->setText(QString::number(this->lsvCon2));
    ui->lsvCon3->setText(QString::number(this->lsvCon3));

    ui->lscvCon1->setText(QString::number(this->lscvCon1));
    ui->lscvCon2->setText(QString::number(this->lscvCon2));
    ui->lscvCon3->setText(QString::number(this->lscvCon3));
    ui->lscvCon4->setText(QString::number(this->lscvCon4));

    ui->ocvCon1->setText(QString::number(this->ocvCon1));
    ui->ocvCon2->setText(QString::number(this->ocvCon2));


}

void constraintsDialog::on_buttonBox_accepted()
{
    this->assignAllConstraints();
}

void constraintsDialog::assignAllConstraints()
{
    this->spCon1 = ui->spCon1->text().toDouble();
    this->spCon2 = ui->spCon2->text().toInt();
    this->spCon3 = ui->spCon3->text().toInt();

    this->lsvCon1 = ui->lsvCon1->text().toInt();
    this->lsvCon2 = ui->lsvCon2->text().toDouble();
    this->lsvCon3 = ui->lsvCon3->text().toDouble();

    this->lscvCon1 = ui->lscvCon1->text().toInt();
    this->lscvCon2 = ui->lscvCon2->text().toDouble();
    this->lscvCon3 = ui->lscvCon3->text().toInt();
    this->lscvCon4 = ui->lscvCon4->text().toDouble();

    this->ocvCon1 = ui->ocvCon1->text().toInt();
    this->ocvCon2 = ui->ocvCon2->text().toInt();

    this->firstTime = false;
}

void constraintsDialog::setConstraintsLineEdits()
{
    ui->spCon1->setValidator(new QDoubleValidator(-99999999, 9999999,5, this));
    ui->spCon2->setValidator(new QIntValidator(-9999999,99999999,this));
    ui->spCon3->setValidator(new QIntValidator(-9999999,99999999,this));

    ui->lsvCon1->setValidator(new QIntValidator(-9999999,99999999,this));
    ui->lsvCon2->setValidator(new QDoubleValidator(-99999999, 9999999, 5, this));
    ui->lsvCon3->setValidator(new QDoubleValidator(-99999999, 9999999, 5,this));



    ui->lscvCon1->setValidator(new QIntValidator(-9999999,99999999,this));
    ui->lscvCon3->setValidator(new QIntValidator(-9999999,99999999,this));
    ui->lscvCon2->setValidator(new QDoubleValidator(-99999999, 9999999,5, this));
    ui->lscvCon4->setValidator(new QDoubleValidator(-99999999, 9999999,5, this));


    ui->ocvCon1->setValidator(new QIntValidator(-9999999,99999999,this));
    ui->ocvCon2->setValidator(new QIntValidator(-9999999,99999999,this));

}
