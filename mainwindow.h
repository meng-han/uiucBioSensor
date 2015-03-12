#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
//! [0]
#include <QtCore/QList>
#include <QtCore/QDebug>
#include <QDialog>
#include <QMessageBox>

#include "settingsdialog.h"
#include "aboutdialog.h"

#include "validateexp.h"

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
    void on_e1LSCVRadioButton_clicked();
    void on_e2LSCVRadioButton_clicked();
    void enable_all_radioButtonE1();
    void enable_all_radioButtonE2();
    void on_e1NoneRadioButton_clicked();
    void on_e2NoneRadioButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_editPushButton_clicked();
    void on_savePushButton_clicked();
    void e1HideFourthRow();
    void e2HideFourthRow();


private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QByteArray receivedData;
    SettingsDialog *settings;
    // MODE: 1, SET POTENTIAL; 2, LSV; 3, OCV; 4, LSCV.
    int e1Mode;
    int e2Mode;
    QStringList e1e2Experiments;  //Records all experiments in a list
    QString constructExpString();
    validateExp validator;
    QPalette *readOnlyPalette = new QPalette();
    QPalette *normalPalette = new QPalette();
    void setToNormalPalette();
    void setToReadOnlyPalette();
    int currentEditting;

};

#endif // MAINWINDOW_H
