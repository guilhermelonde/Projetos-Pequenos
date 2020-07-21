#include "editagerais.h"
#include "ui_editagerais.h"
#include "stringfrom.h"
#include <iostream>

EditaGerais::EditaGerais(QWidget *parent) :
    JanelasEdicao(parent),
    ui(new Ui::EditaGerais)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);

    QStringList titulos;
    titulos << "Palavras" << "Traduções";

    ui->tabela->setHorizontalHeaderLabels(titulos);
    ui->tabela->horizontalHeader()->setVisible(true);
    ui->tabela->verticalHeader()->setVisible(true);
}

EditaGerais::~EditaGerais()
{
    delete ui;
}

void EditaGerais::Parametro(Dicionario *D, int *alt, QLabel *s, MapaTeclado *M, int *PrimSequencia, int *UltmSequencia)
{
    barraStatus = s;
    PrimDaSequencia = PrimSequencia;
    UltmDaSequencia = UltmSequencia;
    Alteracoes = alt;
    MT = M;
    Dic = D;
    atualizar();
}

void EditaGerais::modoLista()
{

}

void EditaGerais::modoListaSelecionadas()
{

}

void EditaGerais::ultimaTraduzida()
{

}

void EditaGerais::atualizar()
{
    while (ui->tabela->rowCount())
        ui->tabela->removeRow(0);
    for (int i = 0; i < Dic->getTamanho(); i++)
    {
        ui->tabela->insertRow(i);
        ui->tabela->setItem(i, ORIGEM, new QTableWidgetItem(QString::fromStdString(Dic->getPrimeira(i))));
        ui->tabela->setItem(i, TRADU, new QTableWidgetItem(QString::fromStdString(Dic->getSegunda(i))));
    }
    if (Dic->getUltimaTrad() != Dic->getTamanho())
    {
        ui->tabela->selectRow(Dic->getUltimaTrad());
        ui->tabela->clearSelection();
        ui->tabela->item(Dic->getUltimaTrad(), 1)->setSelected(true);
        ui->tabela->setFocus();
    }
}

void EditaGerais::resizeEvent(QResizeEvent *event)
{
    int largura = ui->tabela->width() - ui->tabela->verticalHeader()->width();
    larguraA = (float)largura * 0.35;
    larguraB = (float)largura * 0.65 - 20;
    ui->tabela->setColumnWidth(0, larguraA);
    ui->tabela->setColumnWidth(1, larguraB);
}

void EditaGerais::on_inverter_pressed()
{
    *Alteracoes = 1;
    vector <string> Novo;
    StringFrom::InverteOrdemVetor(Novo, Dic->Dic, Dic->getFor());
    Dic->limpar();
    Dic->setSrcFor(Dic->getFor(), Dic->getSrc());
    for (int i = 0; i < Novo.size(); i++)
        Dic->setLinha(Novo[i]);
    Novo.clear();
    *UltmDaSequencia = Dic->getUltimaTrad();
    *PrimDaSequencia = Dic->getUltimaTrad();
    barraStatus->setText("Traduções realizadas em sequência agora: " + QString::number(*UltmDaSequencia - *PrimDaSequencia) + "\tTraduções totais: " + QString::number(Dic->getTraducoes()) + "\tProgresso total: " + QString::number(Dic->getPorcentagem()) + "%");
    atualizar();
}
