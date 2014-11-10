#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
//! [0]
#include <QtCore/QList>
#include <QtCore/QDebug>
#include <QDialog>

#include "settingsdialog.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startPushButton_clicked();
    void onSerialReceived();

    void on_stopPushButton_clicked();

    void on_actionConfigure_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QByteArray receivedData;
    SettingsDialog *settings;

};

#endif // MAINWINDOW_H
