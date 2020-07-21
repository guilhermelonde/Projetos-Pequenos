/*
 * Guilherme Pereira Porto Londe - 20151002803577
 * Estrutura de Dados I - C01
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(w.width(), w.height() + 1);

    return a.exec();
}
