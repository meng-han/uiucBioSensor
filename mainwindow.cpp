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

    ui->e1SPRadioButton->click();
    this->on_e1SPRadioButton_clicked();

    ui->e2SPRadioButton->click();
    this->on_e2SPRadioButton_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_startPushButton_clicked
 * This method is triggerred by clicking on start button
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

    if (tempReceivedData.size()!=4)
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

void MainWindow::on_e1SPRadioButton_clicked()
{
    this->e1Mode = 1; //SET POTENTIAL = 1
    ui->e1Label1->setText("Anode Potential = ");
    ui->e1Label2->setText("V");
    if (ui->e1Label3->isHidden()) ui->e1Label3->show();
    if (ui->e1Label4->isHidden()) ui->e1Label4->show();
    if (ui->e1LineEdit2->isHidden()) ui->e1LineEdit2->show();
    ui->e1Label3->setText("Duration = ");
    ui->e1Label4->setText("min");

    ui->e1LineEdit1->setValidator(new QDoubleValidator(-100, 0, 5, this));
    ui->e1LineEdit2->setValidator(new QIntValidator(0, 9999999, this));

}

void MainWindow::on_e2SPRadioButton_clicked()
{
    this->e2Mode = 1; //SET POTENTIAL = 1
    ui->e2Label1->setText("Anode Potential = ");
    ui->e2Label2->setText("V");
    if (ui->e2Label3->isHidden()) ui->e2Label3->show();
    if (ui->e2Label4->isHidden()) ui->e2Label4->show();
    if (ui->e2LineEdit2->isHidden()) ui->e2LineEdit2->show();
    ui->e2Label3->setText("Duration = ");
    ui->e2Label4->setText("min");

    ui->e2LineEdit1->setValidator(new QDoubleValidator(-100, 0, 5, this));
    ui->e2LineEdit2->setValidator(new QIntValidator(0, 9999999, this));
}

void MainWindow::on_e1LSVRadioButton_clicked()
{
    this->e1Mode = 2; //LSV = 2
    ui->e1Label1->setText("Scan Rate = ");
    ui->e1Label2->setText("mV/s");
    if (ui->e1Label3->isHidden()) ui->e1Label3->show();
    if (ui->e1Label4->isHidden()) ui->e1Label4->show();
    if (ui->e1LineEdit2->isHidden()) ui->e1LineEdit2->show();
    ui->e1Label3->setText("Max Anode = ");
    ui->e1Label4->setText("V");

    ui->e1LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e1LineEdit2->setValidator(new QDoubleValidator(-100, 0, 5, this));

}

void MainWindow::on_e2LSVRadioButton_clicked()
{
    this->e2Mode = 2; //LSV = 2;
    ui->e2Label1->setText("Scan Rate = ");
    ui->e2Label2->setText("mV/s");
    if (ui->e2Label3->isHidden()) ui->e2Label3->show();
    if (ui->e2Label4->isHidden()) ui->e2Label4->show();
    if (ui->e2LineEdit2->isHidden()) ui->e2LineEdit2->show();
    ui->e2Label3->setText("Max Anode = ");
    ui->e2Label4->setText("V");

    ui->e2LineEdit1->setValidator(new QIntValidator(0, 9999999, this));
    ui->e2LineEdit2->setValidator(new QDoubleValidator(-100, 0, 5, this));
}

void MainWindow::on_e1OCVRadioButton_clicked()
{
    this->e1Mode = 3; //OCV = 3;
    ui->e1Label1->setText("Duration = ");
    ui->e1Label2->setText("min");
    ui->e1Label3->hide();
    ui->e1Label4->hide();
    ui->e1LineEdit2->hide();

    ui->e1LineEdit1->setValidator(new QIntValidator(0, 9999999, this));

}

void MainWindow::on_e2OCVRadioButton_clicked()
{
    this->e2Mode = 3; //OCV = 3;
    ui->e2Label1->setText("Duration = ");
    ui->e2Label2->setText("min");
    ui->e2Label3->hide();
    ui->e2Label4->hide();
    ui->e2LineEdit2->hide();

    ui->e1LineEdit1->setValidator(new QIntValidator(0, 9999999, this));

}

void MainWindow::on_addToButton_clicked()
{
    QStringList modeList;
    modeList.append("Set Potential");
    modeList.append("LSV");
    modeList.append("OCV");
    //The following validation needs to be stronger.
    //Check whether there is parameters;
    //Check whether input parameters are valid;
    if ( (this->e1Mode == 1 || this->e1Mode == 2 || this->e1Mode == 3) && (this->e2Mode == 1 || this->e2Mode == 2 || this->e2Mode == 3))
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(modeList[this->e1Mode - 1]);
        ui->tableWidget->setItem(row, 0, item);
        item->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *itemE2 = new QTableWidgetItem(modeList[this->e2Mode - 1]);
        ui->tableWidget->setItem(row, 1, itemE2);
        itemE2->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_deleteAllPushButton_clicked()
{
    // Clear table widget
    int row = ui->tableWidget->rowCount();
    while(row>0)
    {
        ui->tableWidget->removeRow(0);
        row --;
    }
}

void MainWindow::on_deletePushButton_clicked()
{
    QList<QTableWidgetItem *> selectedFiles = ui->tableWidget->selectedItems();
    for (int i = selectedFiles.size() - 1; i >= 0; i -= 7)
    {
        int rowToDelete = selectedFiles[i]->row();
        ui->tableWidget->removeRow(rowToDelete);
    }
}
