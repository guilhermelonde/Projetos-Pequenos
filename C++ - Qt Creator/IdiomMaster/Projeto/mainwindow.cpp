#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <string>
#include "abrirrotinadearquivo.h"
#include "verlista.h"
#include "stringfrom.h"
#include "niveldificuldade.h"
#include "verlistaselecao.h"
#include "pratica.h"
#include "modoedicao.h"
#include "interacaobd.h"
#include <iostream>

string end_dir = "C://";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exibir_prog_clicked()
{
    VerLista V;
    V.setWindowFlags(Qt::Window);
    V.Mostrar(&D);
    V.exec();
}

void MainWindow::on_praticar_clicked()
{
    if (!D.getUltimaTrad())
    {
        QMessageBox::critical(0," ","Não há nenhuma palavra traduzida!");
        return;
    }
    Pratica P;
    P.setModal(true);
    P.setWindowFlags(Qt::Window);
    bool podeExecutar = 0;
    int Nivel = 0;
    NivelDificuldade ND;
    ND.setModal(true);
    ND.Parametro(&Nivel);
    ND.exec();
    if (!Nivel)
        return;
    vector <QString> A;
    vector <QString> B;
    VerListaSelecao VLS;
    VLS.setWindowFlags(Qt::Window);
    VLS.Parametro(&D, &P, A, B, Nivel, &podeExecutar);
    VLS.exec();
    if (!podeExecutar)
        return;
    this->hide();
    P.rodar();
    P.exec();
    this->show();
}

void MainWindow::on_entrar_dicionario_pressed()
{
    if (D.getSrc() == "")
    {
        QMessageBox::critical(0," ","Não há nenhum dicionário atual!");
        return;
    }
    ModoEdicao ED;
    ED.Parametro(&D);
    ED.setWindowFlags(Qt::Window);
    this->hide();
    ED.exec();
    this->show();
}

void MainWindow::on_CarregarDic_clicked()
{
    if (StringFrom::IdiomaValido(ui->De->text().toStdString()) == 0)
    {
        QMessageBox::critical(0," ","Erro! Idioma de origem não reconhecido");
        return;
    }
    if (StringFrom::IdiomaValido(ui->Para->text().toStdString()) == 0)
    {
        QMessageBox::critical(0," ","Erro! Idioma de saída não reconhecido");
        return;
    }
    D.setSrcFor(ui->De->text().toStdString(), ui->Para->text().toStdString());
}
