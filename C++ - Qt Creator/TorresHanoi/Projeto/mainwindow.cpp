#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nivel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NivelAtual = 0;
    tj = new TelaJogo (this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_novoJogo_pressed()
{
    Nivel N;
    int NivelD;
    N.setModal(true);
    N.setGeometry(this->x() + (this->width() - N.width())/2, 20 + this->y() + (this->height() - N.height())/2, N.width(), N.height());
    N.parametroNivel(&NivelD);
    N.exec();
    if (!NivelD)
        return;
    tj->labelMovimentos(ui->labelMovimentos);
    tj->botoesFazerDesfazer(ui->desfazer, ui->refazer);
    tj->setaDiscos(NivelD);
}

void MainWindow::on_desfazer_pressed()
{
    tj->desfazer();
}

void MainWindow::on_refazer_pressed()
{
    tj->refazer();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int x = ui->frame->x() + (ui->frame->width() - tj->width())/2;
    int y = ui->frame->y() + (ui->frame->height() - tj->height())/2;
    tj->setGeometry(x, y, tj->width(), tj->height());
}

