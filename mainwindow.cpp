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
