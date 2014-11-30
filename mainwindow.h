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

    void on_e1SPRadioButton_clicked();

    void on_e2SPRadioButton_clicked();

    void on_e1LSVRadioButton_clicked();

    void on_e2LSVRadioButton_clicked();

    void on_e1OCVRadioButton_clicked();

    void on_e2OCVRadioButton_clicked();

    void on_addToButton_clicked();

    void on_deleteAllPushButton_clicked();

    void on_deletePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QByteArray receivedData;
    SettingsDialog *settings;
    // MODE: 1, SET POTENTIAL; 2, LSV; 3, OCV.
    int e1Mode;
    int e2Mode;

};

#endif // MAINWINDOW_H
