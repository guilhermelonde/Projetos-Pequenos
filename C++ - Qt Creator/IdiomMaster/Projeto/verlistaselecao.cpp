#include "verlistaselecao.h"
#include "ui_verlistaselecao.h"
#include "QTableWidgetItem"
#include "queue"
#include "QTableWidgetSelectionRange"
using namespace std;

VerListaSelecao::VerListaSelecao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerListaSelecao)
{
    ui->setupUi(this);
    setWindowTitle("Selecionar palavras para praticar");
    QStringList titulos;
    titulos << "Palavras" << "Traduções" << "Praticada";
    incluidas = 0;
    ui->tabela->setHorizontalHeaderLabels(titulos);
    ui->tabela->setColumnWidth(1, 200);
    ui->tabela->setColumnWidth(2, 80);
    ui->tabela->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->IrParaLinha->addItem("a primeira linha");
    ui->IrParaLinha->addItem("a última linha");
    ui->IrParaLinha_2->addItem("abaixo");
    ui->IrParaLinha_2->addItem("acima");
    ui->buscarPalavrasPara->addItem("abaixo");
    ui->buscarPalavrasPara->addItem("acima");
    ui->buscarTraducoesPara->addItem("abaixo");
    ui->buscarTraducoesPara->addItem("acima");
    ui->selecionarPalavrasPara->addItem("abaixo");
    ui->selecionarPalavrasPara->addItem("acima");
}

VerListaSelecao::~VerListaSelecao()
{
    delete ui;
}

void VerListaSelecao::Parametro(Dicionario *D, Pratica *P, vector <QString> &A, vector <QString> &B, int Nivel, bool *podeExecutar)
{
    Pra = P;
    Dic = D;
    Va = &A;
    Vb = &B;
    N = Nivel;
    PE = podeExecutar;
    for (int i = 0; i < D->getUltimaTrad(); i++)
    {
        ui->tabela->insertRow(i);
        ui->tabela->setItem(i, ORIGEM, new QTableWidgetItem(QString::fromStdString(D->getPrimeira(i))));
        ui->tabela->setItem(i, TRADU, new QTableWidgetItem(QString::fromStdString(D->getSegunda(i))));
        ui->tabela->setItem(i, PRATI, new QTableWidgetItem(QString::fromStdString(D->Praticada[i] == 1 ? "Sim" : "Não")));
    }
}

void VerListaSelecao::on_tabela_itemSelectionChanged()
{
    QList <QTableWidgetItem*> QL = ui->tabela->selectedItems();
    if (QL.empty())
        return;
    map <int, bool> MM;
    int li = QL.front()->row() + 1;
    int lf = QL.back()->row() + 1;
    for (int i = 0; i < QL.size(); i++)
        MM[QL.operator [](i)->row()] = 1;
    int sz = MM.size();
    ui->linhainicial->setText(QString::number(li));
    ui->linhafinal->setText(QString::number(lf));
    ui->selecionadas->setText(QString::number(sz));
    if (sz == 1)
    {
        ui->incluirlinhas->setText("incluir linha atual");
        ui->excluirlinhas->setText("excluir linha atual");
    }
    else
    {
        ui->incluirlinhas->setText("incluir linhas atuais");
        ui->excluirlinhas->setText("excluir linhas atuais");
    }
}

void VerListaSelecao::on_incluirlinhas_pressed()
{
    QList <QTableWidgetItem*> QL = ui->tabela->selectedItems();
    if (!QL.size())
        return;
    queue <int>MQ;
    MQ.push(QL.front()->row());
    for (int i = 1; i < QL.size(); i++)
    {
        QTableWidgetItem *Q = QL.operator [](i);
        if (MQ.back() != Q->row())
            MQ.push(Q->row());
    }
    while (!MQ.empty())
    {
        ui->tabela->QTableWidget::selectRow(MQ.front());
        QList <QTableWidgetItem*> QL3 = ui->tabela->selectedItems();
        if (QL3.front()->backgroundColor() != Qt::lightGray)
        {
            while(!QL3.empty())
            {
                QL3.front()->setBackgroundColor(Qt::lightGray);
                QL3.pop_front();
            }
            incluidas++;
        }
        MQ.pop();
    }
    ui->incluidas->setText(QString::number(incluidas));
}

void VerListaSelecao::on_excluirlinhas_pressed()
{
    QList <QTableWidgetItem*> QL = ui->tabela->selectedItems();
    if (!QL.size())
        return;
    queue <int>MQ;
    MQ.push(QL.front()->row());
    for (int i = 1; i < QL.size(); i++)
    {
        QTableWidgetItem *Q = QL.operator [](i);
        if (MQ.back() != Q->row())
            MQ.push(Q->row());
    }
    while (!MQ.empty())
    {
        ui->tabela->selectRow(MQ.front());
        QList <QTableWidgetItem*> QL3 = ui->tabela->selectedItems();

        if (QL3.front()->backgroundColor() == Qt::lightGray)
        {
            while(!QL3.empty())
            {
                QL3.front()->setBackgroundColor(Qt::white);
                QL3.pop_front();
            }
            incluidas--;
        }
        MQ.pop();
    }
    ui->incluidas->setText(QString::number(incluidas));
}

void VerListaSelecao::on_incluirtodas_pressed()
{
    int Tam = Dic->getUltimaTrad();
    ui->tabela->selectAll();
    QList <QTableWidgetItem*> QL3 = ui->tabela->selectedItems();
    while (!QL3.empty())
    {
        QL3.front()->setBackgroundColor(Qt::lightGray);
        //QL3.back()->setBackgroundColor(Qt::lightGray);
        QL3.pop_front();
        //QL3.pop_back();
    }
    ui->tabela->selectRow(Tam - 1);
    incluidas = Tam;
    ui->incluidas->setText(QString::number(incluidas));
}

void VerListaSelecao::on_excluirtodas_pressed()
{
    int Tam = Dic->getTamanho();
    ui->tabela->selectAll();
    QList <QTableWidgetItem*> QL3 = ui->tabela->selectedItems();
    while (!QL3.empty())
    {
        QL3.front()->setBackgroundColor(Qt::white);
        //QL3.back()->setBackgroundColor(Qt::white);
        QL3.pop_front();
        //QL3.pop_back();
    }
    ui->tabela->selectRow(Tam - 1);
    incluidas = 0;
    ui->incluidas->setText(QString::number(incluidas));
}

void VerListaSelecao::on_irparalinha_clicked()
{
    if (ui->IrParaLinha->currentIndex() == 0)
        ui->tabela->selectRow(0);
    if (ui->IrParaLinha->currentIndex() == 1)
        ui->tabela->selectRow(Dic->getUltimaTrad() - 1);
}

void VerListaSelecao::on_irparalinha_2_pressed()
{
    int To = 0;
    if (ui->IrParaLinha_2->currentIndex() == 0)
        To = ui->tabela->currentRow() + ui->linhaIrPara->text().toInt();
    if (ui->IrParaLinha_2->currentIndex() == 1)
        To = ui->tabela->currentRow() - ui->linhaIrPara->text().toInt();
    if (To < 0)
        To = 0;
    if (To >= Dic->getUltimaTrad())
        To = Dic->getUltimaTrad() - 1;
    ui->tabela->selectRow(To);
}

void VerListaSelecao::on_irselecionar_pressed()
{
    ui->tabela->selectRow(ui->tabela->currentRow());
    int top = 0, bottom = 0;
    if (ui->selecionarPalavrasPara->currentIndex() == 0)
    {
        top = ui->tabela->currentRow();
        bottom = ui->tabela->currentRow() + ui->selecionarPalavras->text().toInt();
    }
    if (ui->selecionarPalavrasPara->currentIndex() == 1)
    {
        top = ui->tabela->currentRow() - ui->selecionarPalavras->text().toInt();
        bottom = ui->tabela->currentRow();
    }
    if (top < 0)
        top = 0;
    if (bottom >= Dic->getUltimaTrad())
        bottom = Dic->getUltimaTrad() - 1;
    QTableWidgetSelectionRange SR(top, 0, bottom, 1);
    ui->tabela->setRangeSelected(SR, true);
}

void VerListaSelecao::on_pronto_pressed()
{
    ui->tabela->selectAll();
    QList <QTableWidgetItem*> QL3 = ui->tabela->selectedItems();
    int t = Dic->getUltimaTrad();
    *PE = 0;
    for (int i = 0; i < t && !QL3.empty(); i++)
    {
        if (QL3.front()->backgroundColor() == Qt::lightGray)
        {
            *PE = 1;
            Pra->setLinha(Dic->getLinha(QL3.front()->row()), Dic->getLinha(QL3.front()->row()));
            Pra->setRefDicionario(QL3.front()->row());
        }
        QL3.pop_front();
        QL3.pop_front();
        QL3.pop_front();
    }
    if (*PE == 1)
        Pra->Parametro(Dic->getSrc(), Dic->getFor(), N, Dic);
    this->close();
}

void VerListaSelecao::on_irbuscarorigem_pressed()
{
    int para;
    if (ui->buscarPalavrasPara->currentIndex() == 0)
        para = 1;
    else
        para = -1;
    int k = Dic->procurarPrimeira(ui->linhabuscapalavra->text(), ui->tabela->currentRow(), Dic->getUltimaTrad(), para);
    if (k != -1)
        ui->tabela->selectRow(k);
}

void VerListaSelecao::on_irbuscartraducao_pressed()
{
    int para;
    if (ui->buscarTraducoesPara->currentIndex() == 0)
        para = 1;
    else
        para = -1;
    int k = Dic->procurarSegunda(ui->linhabuscatraducao->text(), ui->tabela->currentRow(), Dic->getUltimaTrad(), para);
    if (k != -1)
        ui->tabela->selectRow(k);
}

void VerListaSelecao::on_linhaIrPara_editingFinished()
{
    ui->irparalinha_2->setFocus();
}

void VerListaSelecao::on_linhabuscapalavra_editingFinished()
{
    ui->irbuscarorigem->setFocus();
}

void VerListaSelecao::on_linhabuscatraducao_editingFinished()
{
    ui->irbuscartraducao->setFocus();
}

void VerListaSelecao::on_selecionarPalavras_editingFinished()
{
    ui->irselecionar->setFocus();
}
