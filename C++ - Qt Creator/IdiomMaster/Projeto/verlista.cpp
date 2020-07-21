#include "verlista.h"
#include "ui_verlista.h"

VerLista::VerLista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerLista)
{
    ui->setupUi(this);
    setWindowTitle("Ver progresso de traduções");
    QStringList titulos;
    titulos << "Palavra" << "Tradução" << "Praticada";
    ui->tabela->setHorizontalHeaderLabels(titulos);
    ui->tabela->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->comboBox->addItem("em palavras abaixo");
    ui->comboBox->addItem("em palavras acima");
    ui->comboBox->addItem("em traduções abaixo");
    ui->comboBox->addItem("em traduções acima");
}

VerLista::~VerLista()
{
    delete ui;
}

void VerLista::Mostrar(Dicionario *D)
{
    Dic = D;
    QString prog = "Progresso: " + QString::number(D->getPorcentagem()) + "%  Última linha traduzida: " + QString::number(D->getUltimaTrad()) + "  Traduções totais: " + QString::number(D->getTraducoes());
    ui->progresso->setText(prog);
    for (int i = 0; i < D->getTamanho(); i++)
    {
        ui->tabela->insertRow(i);
        ui->tabela->setItem(i, ORIGEM, new QTableWidgetItem(QString::fromStdString(D->getPrimeira(i))));
        ui->tabela->setItem(i, TRADU, new QTableWidgetItem(QString::fromStdString(D->getSegunda(i))));
        ui->tabela->setItem(i, PRATI, new QTableWidgetItem(QString::fromStdString(D->Praticada[i] == 1 ? "Sim" : "Não")));
    }
}

void VerLista::on_ok_pressed()
{
    this->close();
}

void VerLista::on_pesquisar_pressed()
{
    int para, ci = ui->comboBox->currentIndex(), k = 0;
    if (ci == 0 || ci == 2)
        para = 1;
    if (ci == 1 || ci == 3)
        para = -1;
    if (ci == 0 || ci == 1)
        k = Dic->procurarPrimeira(ui->linha->text(), ui->tabela->currentRow(), Dic->getUltimaTrad(), para);
    if (ci == 2 || ci == 3)
        k = Dic->procurarSegunda(ui->linha->text(), ui->tabela->currentRow(), Dic->getUltimaTrad(), para);
    if (k != -1)
        ui->tabela->selectRow(k);
}

void VerLista::resizeEvent(QResizeEvent * event)
{
    int wt = ui->tabela->width() - ui->tabela->verticalHeader()->width();
    ui->tabela->setColumnWidth(0, (wt-80) * 0.35);
    ui->tabela->setColumnWidth(1, (wt-80) * 0.65);
    ui->tabela->setColumnWidth(2, 80);
}
