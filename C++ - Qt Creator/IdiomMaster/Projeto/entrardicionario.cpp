#include "entrardicionario.h"
#include "ui_entrardicionario.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <iostream>
#include <QPoint>
#include "sairsemsalvar.h"
#include "stringfrom.h"
#include "novapalavra.h"
#include "celulatabela.h"
#include "QTableWidgetSelectionRange"
#include "exibetraducoesrealizadas.h"

using namespace std;

void ExecutaPopup(QWidget *WG)
{
    WG->show();
}

EntrarDicionario::EntrarDicionario(QWidget *parent) :
    JanelasEdicao(parent),
    ui(new Ui::EntrarDicionario)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);

    QStringList titulos;
    titulos << "Palavras" << "Traduções";

    ui->tabela->setHorizontalHeaderLabels(titulos);
    ui->tabela->horizontalHeader()->setVisible(true);
    ui->tabela->verticalHeader()->setVisible(true);

    Menu = new QMenu (this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    Inserir = Menu->addAction("Inserir nova palavra");
    Remover = Menu->addAction("Remover");
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(contextMenuRequested(const QPoint&)));
    connect(Inserir,SIGNAL(triggered()),this,SLOT(InsereLinha()));
    connect(Remover,SIGNAL(triggered()),this,SLOT(RemoveLinha()));

    ui->buscarPara->addItem("em palavras abaixo");
    ui->buscarPara->addItem("em palavras acima");
    ui->buscarPara->addItem("em traduções abaixo");
    ui->buscarPara->addItem("em traduções acima");
}

EntrarDicionario::~EntrarDicionario()
{
    delete ui;
}

void EntrarDicionario::Parametro(Dicionario *D, int *alt, QLabel *s, MapaTeclado *M, int *PrimSequencia, int *UltmSequencia)
{
    PrimDaSequencia = PrimSequencia;
    UltmDaSequencia = UltmSequencia;
    Alteracoes = alt;
    barraStatus = s;
    MT = M;
    Dic = D;
    barraStatus->setText("Traduções realizadas agora: 0\tTraduções totais: " + QString::number(D->getTraducoes()) + "\tProgresso total: " + QString::number(D->getPorcentagem()) + "%");
    *PrimDaSequencia = D->getUltimaTrad();
    *UltmDaSequencia = D->getUltimaTrad();
    PrimeiraTraduzida = D->getUltimaTrad();
}

void EntrarDicionario::contextMenuRequested(const QPoint& pos)
{
    if (pos.x() > ui->tabela->x() && pos.x() < ui->tabela->width() + ui->tabela->x() && pos.y() > ui->tabela->y() + 25 && pos.y() < ui->tabela->height() + ui->tabela->y() - 25)
        Menu->popup(mapToGlobal(pos));
}

void EntrarDicionario::on_tabela_cellActivated(int row, int column)
{
    EditaItem(row, column);
}

void EntrarDicionario::RemoveLinha()
{
    *Alteracoes = 1;
    Dic->removeLinha(ui->tabela->currentRow());
    EquacaoPrimUltmRemove(ui->tabela->currentRow());
    ui->tabela->removeRow(ui->tabela->currentRow());
    barraStatus->setText("Traduções realizadas agora: " + QString::number(*UltmDaSequencia - *PrimDaSequencia) + "\tTraduções totais: " + QString::number(Dic->getTraducoes()) + "\tProgresso total: " + QString::number(Dic->getPorcentagem()) + "%");
}

void EntrarDicionario::InsereLinha()
{
    QString Palavra;
    NovaPalavra NP;
    NP.setModal(true);
    NP.Parametro(&Palavra);
    NP.exec();
    if (Palavra == "")
        return;
    int k = Dic->setPrimeira(Palavra);
    EquacaoPrimUltmAdiciona(k);
    if (!NovoItem(Palavra, "", k))
    {
        EquacaoPrimUltmRemove(k);
        Dic->removeLinha(k);
    }
}

void EntrarDicionario::AlteraItem(int row, int column, QString Texto)
{
    *Alteracoes = 1;
    if (column == 0)
    {
        string palavraAtual = Dic->getPrimeira(row);
        string traducaoAtual = Dic->getSegunda(row);
        Dic->removeLinha(row);
        ui->tabela->removeRow(row);
        int p = Dic->setPrimeira(Texto);
        Dic->setSegunda(QString::fromStdString(traducaoAtual), p);
        EquacaoPrimUltm(row, p);
        if (!NovoItem(Texto, QString::fromStdString(traducaoAtual), p))
        {
            EquacaoPrimUltm(p, row);
            Dic->removeLinha(p);
            Dic->setPrimeira(QString::fromStdString(palavraAtual), row);
            Dic->setSegunda(QString::fromStdString(traducaoAtual), row);
            NovoItem(QString::fromStdString(palavraAtual), QString::fromStdString(traducaoAtual), row);
        }
    }
    else
    {
        if (Texto == "" && row < *UltmDaSequencia)
            RemoveLinha();
        else
        {
            ui->tabela->item(row, 1)->setText(Texto);
            Dic->setSegunda(Texto, row);
            for (; *UltmDaSequencia < Dic->getTamanho() && Dic->getSegunda(*UltmDaSequencia) != ""; *UltmDaSequencia = *UltmDaSequencia + 1)
            {
                ui->tabela->item(*UltmDaSequencia, 0)->setBackgroundColor(Qt::yellow);
                ui->tabela->item(*UltmDaSequencia, 1)->setBackgroundColor(Qt::yellow);
            }
        }
    }
    barraStatus->setText("Traduções realizadas em sequência agora: " + QString::number(*UltmDaSequencia - *PrimDaSequencia) + "\tTraduções totais: " + QString::number(Dic->getTraducoes()) + "\tProgresso total: " + QString::number(Dic->getPorcentagem()) + "%");
    if (Dic->getTamanho() > Dic->getUltimaTrad())
    {
        ui->PalavraAtual->setText(QString::fromStdString(Dic->getPrimeira(*UltmDaSequencia)));
        ultimaTraduzida();
    }
}

bool EntrarDicionario::NovoItem(QString Palavra, QString Traducao, int P)
{
    QTableWidgetItem *It = new QTableWidgetItem;
    QTableWidgetItem *It2 = new QTableWidgetItem;
    ui->tabela->insertRow(P);
    ui->tabela->setItem(P, 0, It);
    ui->tabela->setItem(P, 1, It2);
    ui->tabela->item(P, 0)->setText(Palavra);
    ui->tabela->setCurrentCell(P, 1);
    if (Traducao != "" || P >= *UltmDaSequencia)
    {
        if (Traducao != "")
            ui->tabela->item(P, 1)->setText(Traducao);
        if (P >= *PrimDaSequencia && P < *UltmDaSequencia)
        {
            ui->tabela->item(P, 0)->setBackgroundColor(Qt::yellow);
            ui->tabela->item(P, 1)->setBackgroundColor(Qt::yellow);
        }
        return 1;
    }
    bool Editado = EditaItem(P, 1);
    if (Editado)
    {
        if (P >= *PrimDaSequencia && P < *UltmDaSequencia)
        {
            ui->tabela->item(P, 0)->setBackgroundColor(Qt::yellow);
            ui->tabela->item(P, 1)->setBackgroundColor(Qt::yellow);
        }
        return 1;
    }
    else
    {
        ui->tabela->removeRow(P);
        return 0;
    }
    return 1;
}

bool EntrarDicionario::EditaItem(int row, int column)
{
    int x, y, w, h;
    QString *Texto;
    x = mapToGlobal(ui->tabela->pos()).x() + ui->tabela->verticalHeader()->width() + ui->tabela->columnViewportPosition(column);
    y = mapToGlobal(ui->tabela->pos()).y() + ui->tabela->horizontalHeader()->height() + ui->tabela->rowViewportPosition(row);
    w = ui->tabela->columnWidth(column);
    h = ui->tabela->rowHeight(row);
    CelulaTabela CT(this);
    CT.setGeometry(x, y, w, h);
    CT.setModal(true);
    if (column == 0)
        Texto = CT.Parametro(ui->tabela->item(row, column)->text(), Dic->getSrc());
    if (column == 1)
        Texto = CT.Parametro(ui->tabela->item(row, column)->text(), MT, Dic->getFor());
    CT.exec();
    AlteraItem(row, column, *Texto);
    return (ui->tabela->item(row, column)->text() != "");
}

void EntrarDicionario::EquacaoPrimUltm(int row, int p)
{
    if (row < *UltmDaSequencia || p < *UltmDaSequencia)
    {
        if (row < *PrimDaSequencia && p >= *PrimDaSequencia)
        {
            *PrimDaSequencia = *PrimDaSequencia - 1;
            if (p >= *UltmDaSequencia)
                *UltmDaSequencia = *UltmDaSequencia - 1;
        }
        if (row >= *PrimDaSequencia && p >= *UltmDaSequencia)
            *UltmDaSequencia = *UltmDaSequencia - 1;
        if (row >= *PrimDaSequencia && p < *PrimDaSequencia)
        {
            *PrimDaSequencia = *PrimDaSequencia + 1;
            if (row >= *UltmDaSequencia)
                *UltmDaSequencia= *UltmDaSequencia + 1;
        }
        if (row >= *UltmDaSequencia && p >= *PrimDaSequencia)
            *UltmDaSequencia = *UltmDaSequencia + 1;
    }
}

void EntrarDicionario::EquacaoPrimUltmRemove(int row)
{
    if (row < *UltmDaSequencia)
    {
        if (row >= *PrimDaSequencia)
            *UltmDaSequencia = *UltmDaSequencia - 1;
        if (row < *PrimDaSequencia)
        {
            *UltmDaSequencia = *UltmDaSequencia - 1;
            *PrimDaSequencia = *PrimDaSequencia - 1;
        }
    }
}

void EntrarDicionario::EquacaoPrimUltmAdiciona(int row)
{
    if (row < *UltmDaSequencia)
    {
        if (row >= *PrimDaSequencia)
            *UltmDaSequencia = *UltmDaSequencia + 1;
        if (row < *PrimDaSequencia)
        {
            *UltmDaSequencia = *UltmDaSequencia + 1;
            *PrimDaSequencia = *PrimDaSequencia + 1;
        }
    }
}

void EntrarDicionario::ultimaTraduzida()
{
    if (*UltmDaSequencia == Dic->getTamanho())
    {
        ui->tabela->selectRow(*UltmDaSequencia - 1);
        ui->tabela->setCurrentCell(*UltmDaSequencia - 1, 1);
        ui->tabela->clearSelection();
        ui->tabela->item(*UltmDaSequencia - 1, 1)->setSelected(true);
        ui->tabela->setFocus();
        return;
    }
    int LinhasAcima = 10, LinhasAbaixo = 10;
    if (*UltmDaSequencia < LinhasAcima)
        LinhasAcima = *UltmDaSequencia;
    if (Dic->getTamanho() - *UltmDaSequencia <= LinhasAbaixo)
        LinhasAbaixo = Dic->getTamanho() - *UltmDaSequencia - 1;
    ui->tabela->selectRow(*UltmDaSequencia - LinhasAcima);
    ui->tabela->selectRow(*UltmDaSequencia + LinhasAbaixo);
    ui->tabela->selectRow(*UltmDaSequencia);
    ui->tabela->setCurrentCell(*UltmDaSequencia, 1);
    ui->tabela->clearSelection();
    ui->tabela->item(*UltmDaSequencia, 1)->setSelected(true);
    ui->tabela->setFocus();
}

void EntrarDicionario::atualizar()
{
    while (ui->tabela->rowCount())
        ui->tabela->removeRow(0);
    for (int i = 0; i < Dic->getTamanho(); i++)
    {
        ui->tabela->insertRow(i);
        ui->tabela->setItem(i, ORIGEM, new QTableWidgetItem(QString::fromStdString(Dic->getPrimeira(i))));
        ui->tabela->setItem(i, TRADU, new QTableWidgetItem(QString::fromStdString(Dic->getSegunda(i))));
    }
    for (int i = *PrimDaSequencia; i < *UltmDaSequencia; i++)
    {
        ui->tabela->item(i, 0)->setBackgroundColor(Qt::yellow);
        ui->tabela->item(i, 1)->setBackgroundColor(Qt::yellow);
    }
    if (Dic->getUltimaTrad() == Dic->getTamanho())
    {
        QMessageBox::warning(0," ","Este dicionário já está 100% traduzido!");
        ui->PalavraAtual->setText("");
    }
    else
    {
        ui->tabela->selectRow(Dic->getUltimaTrad());
        ui->tabela->clearSelection();
        ui->tabela->item(Dic->getUltimaTrad(), 1)->setSelected(true);
        ui->tabela->setFocus();
        ui->PalavraAtual->setText(QString::fromStdString(Dic->getPrimeira(Dic->getUltimaTrad())));
    }
}

void EntrarDicionario::resizeEvent(QResizeEvent * event)
{
    int largura = ui->tabela->width() - ui->tabela->verticalHeader()->width();
    larguraA = (float)largura * 0.35;
    larguraB = (float)largura * 0.65 - 20;
    ui->tabela->setColumnWidth(0, larguraA);
    ui->tabela->setColumnWidth(1, larguraB);
}

void EntrarDicionario::modoLista()
{
    ExibeTraducoesRealizadas ETR;
    ETR.setWindowFlags(Qt::Window);
    ETR.setModal(true);
    for (int i = *PrimDaSequencia; i < *UltmDaSequencia; i++)
        ETR.setItem(Dic->getPrimeira(i), Dic->getSrc(), Dic->getSegunda(i), Dic->getFor());
    ETR.Rodar();
    ETR.exec();
}

void EntrarDicionario::modoListaSelecionadas()
{
    int UltmExib = 0;
    QList <QTableWidgetItem*> QL = ui->tabela->selectedItems();
    ExibeTraducoesRealizadas ETR;
    ETR.setWindowFlags(Qt::Window);
    ETR.setModal(true);
    while (!QL.empty())
    {
        if (UltmExib != QL.front()->row() && Dic->getSegunda(QL.front()->row()) != "")
        {
            ETR.setItem(Dic->getPrimeira(QL.front()->row()), Dic->getSrc(), Dic->getSegunda(QL.front()->row()), Dic->getFor());
            UltmExib = QL.front()->row();
        }
        QL.pop_front();
    }
    ETR.Rodar();
    ETR.exec();

}

void EntrarDicionario::on_linhaBuscar_editingFinished()
{
    ui->buscar->setFocus();
}

void EntrarDicionario::on_buscar_pressed()
{
    int para, ci = ui->buscarPara->currentIndex(), k = 0;
    if (ci == 0 || ci == 2)
        para = 1;
    if (ci == 1 || ci == 3)
        para = -1;
    if (ci == 0 || ci == 1)
        k = Dic->procurarPrimeira(ui->linhaBuscar->text(), ui->tabela->currentRow(), Dic->getTamanho(), para);
    if (ci == 2 || ci == 3)
        k = Dic->procurarSegunda(ui->linhaBuscar->text(), ui->tabela->currentRow(), Dic->getTamanho(), para);
    if (k != -1)
        ui->tabela->selectRow(k);
    ui->tabela->setFocus();
}
