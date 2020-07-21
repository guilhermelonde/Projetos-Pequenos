/*
 * Guilherme Pereira Porto Londe - 2015100280357-7
 * Estrutura de Dados I - C01
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
