#include "mainwindow.h"
#include <QApplication>


/**
 * @brief main
 * @param argc
 * @param argv
 * This is the intro-point of the application.
 * Specify mainwindow to show when start-up
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
