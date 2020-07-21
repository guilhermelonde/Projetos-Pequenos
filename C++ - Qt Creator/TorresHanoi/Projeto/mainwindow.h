#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QMouseEvent>
#include "telajogo.h"

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
    void on_novoJogo_pressed();
    void on_desfazer_pressed();
    void on_refazer_pressed();

private:
    Ui::MainWindow *ui;
    TelaJogo * tj;
    int NivelAtual;
    void resizeEvent(QResizeEvent * event);
};

#endif // MAINWINDOW_H
