#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dicionario.h>
#include "interacaobd.h"

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
    void on_exibir_prog_clicked();
    void on_praticar_clicked();
    void on_entrar_dicionario_pressed();
    //void on_dicionarioReduzido_pressed();
    void on_CarregarDic_clicked();

private:
    Ui::MainWindow *ui;
    Dicionario D;
};

#endif // MAINWINDOW_H
