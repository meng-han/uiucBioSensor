#include "mainwindow.h"
#include "ui_mainwindow.h"
/**
 * @brief MainWindow::MainWindow
 * @param parent
 * Bio-Electrichemical Sensor Project GUI
 * THIS IS THE STARTING WINDOW
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new QSerialPort(this);
    connect(port, SIGNAL(readyRead()), this, SLOT(onSerialReceived()));
    settings = new SettingsDialog;

    readOnlyPalette->setColor(QPalette::Base,Qt::gray);
    normalPalette->setColor(QPalette::Base,Qt::white);

    ui->e1SPRadioButton->click();
    this->on_e1SPRadioButton_clicked();

    ui->e2SPRadioButton->click();
    this->on_e2SPRadioButton_clicked();

    ui->editPushButton->setEnabled(false);
    ui->savePushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_startPushButton_clicked
 * This method is triggerred by clicking on start button
 * THIS WORKS FOR TESTING WITH ARDUINO
 */
void MainWindow::on_startPushButton_clicked()
{
    SettingsDialog::Settings p = settings->settings();
    port->setPortName(p.name);
    port->setBaudRate(p.baudRate);
    port->setDataBits(p.dataBits);
    port->setParity(p.parity);
    port->setStopBits(p.stopBits);
    port->setFlowControl(p.flowControl);
    port->open(QIODevice::ReadWrite);
    qDebug() << port->isOpen();
    QByteArray ba("a");
    port->write(ba);
    port->flush();
    //port->close();
}

/**
 * @brief MainWindow::onSerialReceived
 * Slot for receiving messages
 * This method is for debug only
 */
void MainWindow::onSerialReceived()
{
    //Need some kind of received data ending rule, such as "\r" or "\n"
    QByteArray tempReceivedData = port->readAll();
    this->receivedData.append(tempReceivedData);

    if (tempReceivedData.size() < 4)
    {
        qDebug() << this->receivedData;
        ui->label->setText(this->receivedData);
        this->receivedData.clear();
    }
}


/**
 * @brief MainWindow::on_stopPushButton_clicked
 * Close the port when stop button is clicked
 */
void MainWindow::on_stopPushButton_clicked()
{
    port->close();
}

/**
 * @brief MainWindow::on_actionConfigure_triggered
 * Show configure view.
 */
void MainWindow::on_actionConfigure_triggered()
{
    this->settings->setModal(true);
    this->settings->exec();
}

/**
 * @brief MainWindow::on_actionAbout_triggered
 * When Help -> About is clicked.
 */
void MainWindow::on_actionAbout_triggered()
{
    aboutDialog *about = new aboutDialog(this);
    about->setModal(true);
    about->exec();
}

/************************************RADIO BUTTONS**********************************/

/**
 * @brief MainWindow::on_e1SPRadioButton_clicked
 * SET POTENTIAL
 * ELECTRODE 1
 */
void MainWindow::on_e1SPRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e1SPRadioButton->isChecked())
        ui->e1SPRadioButton->setChecked(true);
    this->e1Mode = 1; //SET POTENTIAL = 1
    this->enable_all_radioButtonE2();
    ui->e2LSVRadioButton->setEnabled(false);
    ui->e2LSCVRadioButton->setEnabled(false);

    ui->e1Label1->setText("Anode Potential = ");
    ui->e1Label2->setText("V");

    if (ui->e1Label3->isHidden()) ui->e1Label3->show();
    if (ui->e1Label4->isHidden()) ui->e1Label4->show();
    if (ui->e1Label5->isHidden()) ui->e1Label5->show();
    if (ui->e1Label6->isHidden()) ui->e1Label6->show();

    if (ui->e1LineEdit2->isHidden()) ui->e1LineEdit2->show();
    if (ui->e1LineEdit3->isHidden()) ui->e1LineEdit3->show();

    ui->e1Label3->setText("Duration = ");
    ui->e1Label4->setText("min");

    ui->e1Label5->setText("Time Interval = ");
    ui->e1Label6->setText("s");

    ui->e1LineEdit1->setValidator(new QDoubleValidator(-100, 0, 5, this));
    ui->e1LineEdit2->setValidator(new QIntValidator(0, 9999999, this));
    ui->e1LineEdit3->setValidator(new QIntValidator(0,999999,this));
}

/**
 * @brief MainWindow::on_e2SPRadioButton_clicked
 * SET POTENTIAL
 * ELECTRODE 2
 */
void MainWindow::on_e2SPRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e2SPRadioButton->isChecked())
        ui->e2SPRadioButton->setChecked(true);
    this->e2Mode = 1; //SET POTENTIAL = 1

    this->enable_all_radioButtonE1();
    ui->e1LSVRadioButton->setEnabled(false);
    ui->e1LSCVRadioButton->setEnabled(false);

    ui->e2Label1->setText("Anode Potential = ");
    ui->e2Label2->setText("V");
    if (ui->e2Label3->isHidden()) ui->e2Label3->show();
    if (ui->e2Label4->isHidden()) ui->e2Label4->show();
    if (ui->e2Label5->isHidden()) ui->e2Label5->show();
    if (ui->e2Label6->isHidden()) ui->e2Label6->show();

    if (ui->e2LineEdit2->isHidden()) ui->e2LineEdit2->show();
    if (ui->e2LineEdit3->isHidden()) ui->e2LineEdit3->show();

    ui->e2Label3->setText("Duration = ");
    ui->e2Label4->setText("min");

    ui->e2Label5->setText("Time Interval = ");
    ui->e2Label6->setText("s");

    ui->e2LineEdit1->setValidator(new QDoubleValidator(-100, 0, 5, this));
    ui->e2LineEdit2->setValidator(new QIntValidator(0, 9999999, this));
    ui->e2LineEdit3->setValidator(new QIntValidator(0,999999,this));
}

/**
 * @brief MainWindow::on_e1LSVRadioButton_clicked
 * LSV
 * ELECTRODE 1
 */

void MainWindow::on_e1LSVRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e1LSVRadioButton->isChecked())
        ui->e1LSVRadioButton->setChecked(true);
    this->e1Mode = 2; //LSV = 2
    this->enable_all_radioButtonE2();
    ui->e2SPRadioButton->setEnabled(false);
    ui->e2LSVRadioButton->setEnabled(false);
    ui->e2LSCVRadioButton->setEnabled(false);

    ui->e1Label1->setText("Scan Rate = ");
    ui->e1Label2->setText("mV/s");
    if (ui->e1Label3->isHidden()) ui->e1Label3->show();
    if (ui->e1Label4->isHidden()) ui->e1Label4->show();
    if (ui->e1LineEdit2->isHidden()) ui->e1LineEdit2->show();
    ui->e1Label3->setText("Max Anode = ");
    ui->e1Label4->setText("V");

    ui->e1LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e1LineEdit2->setValidator(new QDoubleValidator(-100, 0, 5, this));

    ui->e1Label5->hide();
    ui->e1Label6->hide();
    ui->e1LineEdit3->hide();
}


/**
 * @brief MainWindow::on_e2LSVRadioButton_clicked
 * LSV
 * ELECTRODE 2
 */

void MainWindow::on_e2LSVRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e2LSVRadioButton->isChecked())
        ui->e2LSVRadioButton->setChecked(true);
    this->e2Mode = 2; //LSV = 2;

    this->enable_all_radioButtonE1();
    ui->e1SPRadioButton->setEnabled(false);
    ui->e1LSVRadioButton->setEnabled(false);
    ui->e1LSCVRadioButton->setEnabled(false);

    ui->e2Label1->setText("Scan Rate = ");
    ui->e2Label2->setText("mV/s");
    if (ui->e2Label3->isHidden()) ui->e2Label3->show();
    if (ui->e2Label4->isHidden()) ui->e2Label4->show();
    if (ui->e2LineEdit2->isHidden()) ui->e2LineEdit2->show();
    ui->e2Label3->setText("Max Anode = ");
    ui->e2Label4->setText("V");

    ui->e2LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e2LineEdit2->setValidator(new QDoubleValidator(-100, 0, 5, this));

    ui->e2Label5->hide();
    ui->e2Label6->hide();
    ui->e2LineEdit3->hide();
}


/**
 * @brief MainWindow::on_e1OCVRadioButton_clicked
 * OCV
 * ELECTRODE 1
 */

void MainWindow::on_e1OCVRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e1OCVRadioButton->isChecked())
        ui->e1OCVRadioButton->setChecked(true);
    this->e1Mode = 3; //OCV = 3;
    this->enable_all_radioButtonE2();
    ui->e1Label1->setText("Duration = ");
    ui->e1Label2->setText("min");
    ui->e1Label3->setText("Time Interval = ");
    ui->e1Label4->setText("s");
    if (ui->e1Label3->isHidden()) ui->e1Label3->show();
    if (ui->e1Label4->isHidden()) ui->e1Label4->show();
    if (ui->e1LineEdit2->isHidden()) ui->e1LineEdit2->show();

    ui->e1LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e1LineEdit2->setValidator(new QIntValidator(0, 9999999, this));

    ui->e1Label5->hide();
    ui->e1Label6->hide();
    ui->e1LineEdit3->hide();

}


/**
 * @brief MainWindow::on_e2OCVRadioButton_clicked
 * OCV
 * ELECTRODE 2
 */

void MainWindow::on_e2OCVRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e2OCVRadioButton->isChecked())
        ui->e2OCVRadioButton->setChecked(true);
    this->e2Mode = 3; //OCV = 3;
    this->enable_all_radioButtonE1();
    ui->e2Label1->setText("Duration = ");
    ui->e2Label2->setText("min");
    ui->e2Label3->setText("Time Interval = ");
    ui->e2Label4->setText("s");
    if (ui->e2Label3->isHidden()) ui->e2Label3->show();
    if (ui->e2Label4->isHidden()) ui->e2Label4->show();
    if (ui->e2LineEdit2->isHidden()) ui->e2LineEdit2->show();

    ui->e2LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e2LineEdit2->setValidator(new QIntValidator(0, 9999999, this));

    ui->e2Label5->hide();
    ui->e2Label6->hide();
    ui->e2LineEdit3->hide();

}

/**
 * @brief MainWindow::on_e1LSCVRadioButton_clicked
 * LSCV
 * ELECTRODE 1
 */

void MainWindow::on_e1LSCVRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e1LSCVRadioButton->isChecked())
        ui->e1LSCVRadioButton->setChecked(true);
    this->e1Mode = 4; //LSCV = 4
    this->enable_all_radioButtonE2();
    ui->e2SPRadioButton->setEnabled(false);
    ui->e2LSVRadioButton->setEnabled(false);
    ui->e2LSCVRadioButton->setEnabled(false);
    ui->e1Label1->setText("Scan Rate = ");
    ui->e1Label2->setText("mV/s");
    ui->e1Label3->setText("Max Anode = ");
    ui->e1Label4->setText("V");
    ui->e1Label5->setText("# of Cycles");
    ui->e1Label6->hide();
    if (ui->e1Label3->isHidden()) ui->e1Label3->show();
    if (ui->e1Label4->isHidden()) ui->e1Label4->show();
    if (ui->e1LineEdit2->isHidden()) ui->e1LineEdit2->show();
    if (ui->e1Label5->isHidden()) ui->e1Label5->show();
    if (ui->e1LineEdit3->isHidden()) ui->e1LineEdit3->show();

    ui->e1LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e1LineEdit2->setValidator(new QDoubleValidator(-100, 0, 5, this));
    ui->e1LineEdit3->setValidator(new QIntValidator(0, 9999999, this));
}

/**
 * @brief MainWindow::on_e2LSCVRadioButton_clicked
 * LSCV
 * ELECTRODE 2
 */

void MainWindow::on_e2LSCVRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    if(!ui->e2LSCVRadioButton->isChecked())
        ui->e2LSCVRadioButton->setChecked(true);
    this->e2Mode = 4; //LSCV = 4

    this->enable_all_radioButtonE1();
    ui->e1SPRadioButton->setEnabled(false);
    ui->e1LSVRadioButton->setEnabled(false);
    ui->e1LSCVRadioButton->setEnabled(false);

    ui->e2Label1->setText("Scan Rate = ");
    ui->e2Label2->setText("mV/s");
    ui->e2Label3->setText("Max Anode = ");
    ui->e2Label4->setText("V");
    ui->e2Label5->setText("# of Cycles");
    ui->e2Label6->hide();
    if (ui->e2Label3->isHidden()) ui->e2Label3->show();
    if (ui->e2Label4->isHidden()) ui->e2Label4->show();
    if (ui->e2LineEdit2->isHidden()) ui->e2LineEdit2->show();
    if (ui->e2Label5->isHidden()) ui->e2Label5->show();
    if (ui->e2LineEdit3->isHidden()) ui->e2LineEdit3->show();

    ui->e2LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e2LineEdit2->setValidator(new QDoubleValidator(-100, 0, 5, this));
    ui->e2LineEdit3->setValidator(new QIntValidator(0, 9999999, this));
}

void MainWindow::enable_all_radioButtonE1()
{
    ui->e1SPRadioButton->setEnabled(true);
    ui->e1LSVRadioButton->setEnabled(true);
    ui->e1LSCVRadioButton->setEnabled(true);
    ui->e1OCVRadioButton->setEnabled(true);
    ui->e1NoneRadioButton->setEnabled(true);
}

void MainWindow::enable_all_radioButtonE2()
{
    ui->e2SPRadioButton->setEnabled(true);
    ui->e2LSVRadioButton->setEnabled(true);
    ui->e2LSCVRadioButton->setEnabled(true);
    ui->e2OCVRadioButton->setEnabled(true);
    ui->e2NoneRadioButton->setEnabled(true);
}

void MainWindow::on_e1NoneRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    this->enable_all_radioButtonE2();
}

void MainWindow::on_e2NoneRadioButton_clicked()
{
    if(ui->e1LineEdit1->isReadOnly())
    {
        this->setToNormalPalette();
    }
    this->enable_all_radioButtonE1();
}



/************************************END OF RADIO BUTTONS**********************************/


QString MainWindow::constructExpString()
{
    QString tempExp = "";
    tempExp.append(QString::number(this->e1Mode));
    tempExp.append(",");
    tempExp.append(ui->e1LineEdit1->text());
    tempExp.append(",");
    tempExp.append(ui->e1LineEdit2->text());
    tempExp.append(",");
    tempExp.append(ui->e1LineEdit3->text());
    tempExp.append(",");

    tempExp.append(QString::number(this->e2Mode));
    tempExp.append(",");
    tempExp.append(ui->e2LineEdit1->text());
    tempExp.append(",");
    tempExp.append(ui->e2LineEdit2->text());
    tempExp.append(",");
    tempExp.append(ui->e2LineEdit3->text());
    return tempExp;
}

void MainWindow::on_addToButton_clicked()
{
    QStringList modeList;
    modeList.append("Set Potential");
    modeList.append("LSV");
    modeList.append("OCV");
    modeList.append("LSCV");
    //The following validation needs to be stronger.
    //Check whether there is parameters;
    //Check whether input parameters are valid;
    if ( (this->e1Mode == 1 || this->e1Mode == 2 || this->e1Mode == 3 || this->e1Mode == 4)
         && (this->e2Mode == 1 || this->e2Mode == 2 || this->e2Mode == 3 || this->e2Mode == 4))
    {
        QString expString = constructExpString();
        QString result = this->validator.validate(expString);

        QStringList e1e2Results = result.split(";");
        if(e1e2Results[0].startsWith("Y")&&e1e2Results[1].startsWith("Y"))
        {
            this->e1e2Experiments.append(expString);

            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(modeList[this->e1Mode - 1]);
            ui->tableWidget->setItem(row, 0, item);
            item->setTextAlignment(Qt::AlignCenter);

            QTableWidgetItem *itemE2 = new QTableWidgetItem(modeList[this->e2Mode - 1]);
            ui->tableWidget->setItem(row, 1, itemE2);
            itemE2->setTextAlignment(Qt::AlignCenter);
        }
        else{
            QString errorMessage = "Please refer to following errors:\n\n";
            errorMessage.append("Electrode 1: \n\t");
            errorMessage.append(e1e2Results[0]);
            errorMessage.append("\n\n");
            errorMessage.append("Electrode 2: \n\t");
            errorMessage.append(e1e2Results[1]);
            QMessageBox::warning(this, "Error", errorMessage
                                            );
        }

        qDebug() << expString;
        qDebug() << result;

    }
}

void MainWindow::on_deleteAllPushButton_clicked()
{
    // Clear on front end
    // Clear table widget
    int row = ui->tableWidget->rowCount();
    while(row>0)
    {
        ui->tableWidget->removeRow(0);
        row --;
    }
    // Clear on back end
    this->e1e2Experiments.clear();
}
/**
 * @brief MainWindow::on_deletePushButton_clicked
 * Delete a certain experiment
 * Front end: remove from table
 * Back end: remove from experiment list
 */
void MainWindow::on_deletePushButton_clicked()
{
    QList<QTableWidgetItem *> selectedFiles = ui->tableWidget->selectedItems();
    qDebug() << selectedFiles.size();
    if(selectedFiles.size()>0)
    {
        //Remove table row at front-end
        int rowToDelete = selectedFiles[0]->row();
        ui->tableWidget->removeRow(rowToDelete);
        //Remove corresponding items at back-end
        this->e1e2Experiments.removeAt(rowToDelete);
    }

}

void MainWindow::setToNormalPalette(){
    ui->editPushButton->setEnabled(false);
    ui->savePushButton->setEnabled(false);

    ui->e1LineEdit1->setReadOnly(false);
    ui->e1LineEdit1->setPalette(*normalPalette);
    ui->e1LineEdit2->setReadOnly(false);
    ui->e1LineEdit2->setPalette(*normalPalette);
    ui->e1LineEdit3->setReadOnly(false);
    ui->e1LineEdit3->setPalette(*normalPalette);
    ui->e2LineEdit1->setReadOnly(false);
    ui->e2LineEdit1->setPalette(*normalPalette);
    ui->e2LineEdit2->setReadOnly(false);
    ui->e2LineEdit2->setPalette(*normalPalette);
    ui->e2LineEdit3->setReadOnly(false);
    ui->e2LineEdit3->setPalette(*normalPalette);
}


/**
 * @brief MainWindow::on_tableWidget_cellDoubleClicked
 * @param row
 * @param column
 * When a cell/row gets double clicked, it will retrive its previous input data and display it
 */
void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QStringList inputData = this->e1e2Experiments[row].split(",");
    this->currentEditting = row;
    switch(inputData[0].toInt())
    {
    case 1:this->on_e1SPRadioButton_clicked();break;
    case 2:this->on_e1LSVRadioButton_clicked();break;
    case 3:this->on_e1OCVRadioButton_clicked();break;
    case 4:this->on_e1LSCVRadioButton_clicked();break;
    default:break;
    }
    switch(inputData[4].toInt())
    {
    case 1:this->on_e2SPRadioButton_clicked();break;
    case 2:this->on_e2LSVRadioButton_clicked();break;
    case 3:this->on_e2OCVRadioButton_clicked();break;
    case 4:this->on_e2LSCVRadioButton_clicked();break;
    default:break;
    }
    ui->e1LineEdit1->setText(inputData[1]);
    ui->e1LineEdit2->setText(inputData[2]);
    ui->e1LineEdit3->setText(inputData[3]);
    ui->e2LineEdit1->setText(inputData[5]);
    ui->e2LineEdit2->setText(inputData[6]);
    ui->e2LineEdit3->setText(inputData[7]);
    this->setToReadOnlyPalette();
    ui->editPushButton->setEnabled(true);

    qDebug() << this->e1e2Experiments.size();
}

void MainWindow::setToReadOnlyPalette()
{
    ui->e1LineEdit1->setReadOnly(true);
    ui->e1LineEdit1->setPalette(*readOnlyPalette);
    ui->e1LineEdit2->setReadOnly(true);
    ui->e1LineEdit2->setPalette(*readOnlyPalette);
    ui->e1LineEdit3->setReadOnly(true);
    ui->e1LineEdit3->setPalette(*readOnlyPalette);
    ui->e2LineEdit1->setReadOnly(true);
    ui->e2LineEdit1->setPalette(*readOnlyPalette);
    ui->e2LineEdit2->setReadOnly(true);
    ui->e2LineEdit2->setPalette(*readOnlyPalette);
    ui->e2LineEdit3->setReadOnly(true);
    ui->e2LineEdit3->setPalette(*readOnlyPalette);
}

void MainWindow::on_editPushButton_clicked()
{
    this->setToNormalPalette();
    ui->savePushButton->setEnabled(true);
}

void MainWindow::on_savePushButton_clicked()
{
    QStringList modeList;
    modeList.append("Set Potential");
    modeList.append("LSV");
    modeList.append("OCV");
    modeList.append("LSCV");
    //The following validation needs to be stronger.
    //Check whether there is parameters;
    //Check whether input parameters are valid;
    if ( (this->e1Mode == 1 || this->e1Mode == 2 || this->e1Mode == 3 || this->e1Mode == 4)
         && (this->e2Mode == 1 || this->e2Mode == 2 || this->e2Mode == 3 || this->e2Mode == 4))
    {
        QString expString = constructExpString();
        QString result = this->validator.validate(expString);

        QStringList e1e2Results = result.split(";");
        if(e1e2Results[0].startsWith("Y")&&e1e2Results[1].startsWith("Y"))
        {
            this->e1e2Experiments[currentEditting] = expString;
            this->setToReadOnlyPalette();
            ui->savePushButton->setEnabled(false);

        }
        else{
            QString errorMessage = "Please refer to following errors:\n\n";
            errorMessage.append("Electrode 1: \n\t");
            errorMessage.append(e1e2Results[0]);
            errorMessage.append("\n\n");
            errorMessage.append("Electrode 2: \n\t");
            errorMessage.append(e1e2Results[1]);
            QMessageBox::warning(this, "Error", errorMessage
                                            );
        }
        qDebug() << expString;
        qDebug() << result;
    }

}
