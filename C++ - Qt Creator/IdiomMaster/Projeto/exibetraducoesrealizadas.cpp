#include "exibetraducoesrealizadas.h"
#include "ui_exibetraducoesrealizadas.h"
#include "stringfrom.h"

ExibeTraducoesRealizadas::ExibeTraducoesRealizadas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExibeTraducoesRealizadas)
{
    ui->setupUi(this);
    this->setWindowTitle("");
    this->setWindowFlags(windowFlags() | Qt::Popup);
    Editavel = 0;
    ui->QtColunas->setMinimum(1);
    ui->QtColunas->setMaximum(10);
    ui->QtColunas->setValue(1);
    ui->largurasPalavras->setMinimum(1);
    ui->largurasPalavras->setMaximum(40);
    ui->largurasPalavras->setValue(20);
    ui->largurasTraducoes->setMinimum(1);
    ui->largurasTraducoes->setMaximum(60);
    ui->largurasTraducoes->setValue(20);
    Editavel = 1;
    ui->TextoLayout->addWidget(ui->TextoCor1, 0, 0, Qt::AlignCenter);
    ui->TextoLayout->addWidget(ui->TextoCor2, 0, 0, Qt::AlignCenter);
}

ExibeTraducoesRealizadas::~ExibeTraducoesRealizadas()
{
    delete ui;
}

void ExibeTraducoesRealizadas::setItem(string Palavra, string Lf, string Traducao, string Lt)
{
    while (Palavra[0] == 10)
        Palavra.erase(0, 1);
    while (Palavra[Palavra.size() - 1] == '\t')
        Palavra = Palavra.substr(0, Palavra.size() - 1);
    LargurasPal.push_back(StringFrom::QuantidadeCaracteres(Palavra, Lf));
    LargurasTrad.push_back(StringFrom::QuantidadeCaracteres(Traducao, Lt));
    Palavras.push_back(Palavra);
    Traducoes.push_back(Traducao);
}

void ExibeTraducoesRealizadas::Rodar()
{
    ui->QtColunas->setValue(2);
}

void ExibeTraducoesRealizadas::on_QtColunas_valueChanged(int arg1)
{
    if (!Editavel)
        return;

    string Label1 = "|", Label2 = "|";
    int ColunasTotais = arg1 * 2, Divisao = Palavras.size() / arg1, Resto = Palavras.size()%arg1, LinhasTotais, UltimaLarguraMaxima = LarguraPalavra * arg1 + LarguraTraducao * arg1;
    LinhasTotais = Divisao + !(!Resto);
    if (!Resto)
        Resto = arg1;

    //Calculando quantidade de caracteres de strings, quantidade de espaços entre palavras e larguras de linhas
    int MatrizQtChar[LinhasTotais][ColunasTotais];
    int MatrizEspacosELargura[LinhasTotais][ColunasTotais + 1];
    for (int i = 0; i < LinhasTotais; i++)
    {
        int Sobresalente = 0, LarguraDaLinha = 0;
        for (int j = 0; j < arg1; j++)
        {
            int Ind = IndItemEm(i, j, LinhasTotais, Resto), L1 = 0, L2 = 0;
            if (Ind != -1)
            {
                L1 = LargurasPal[Ind];
                L2 = LargurasTrad[Ind];
            }
            MatrizQtChar[i][j*2] = L1;
            MatrizQtChar[i][j*2+1] = L2;
            MatrizEspacosELargura[i][j*2] = QtEspacos(L1, LarguraPalavra, Sobresalente);
            MatrizEspacosELargura[i][j*2+1] = QtEspacos(L2, LarguraTraducao, Sobresalente);
            LarguraDaLinha = LarguraDaLinha + L1 + MatrizEspacosELargura[i][j*2] + L2 + MatrizEspacosELargura[i][j*2+1];
        }
        MatrizEspacosELargura[i][ColunasTotais] = LarguraDaLinha;
        if (LarguraDaLinha > UltimaLarguraMaxima)
            UltimaLarguraMaxima = LarguraDaLinha;
    }

    //Justificando as linhas com espaços após o texto
    for (int i = 0; i < LinhasTotais; i++)
        if (MatrizEspacosELargura[i][ColunasTotais] < UltimaLarguraMaxima)
            MatrizEspacosELargura[i][ColunasTotais - 1] =  MatrizEspacosELargura[i][ColunasTotais - 1] + (UltimaLarguraMaxima - MatrizEspacosELargura[i][ColunasTotais]);

    //Montando as labels TextoCor1 e TextoCor2
    for (int i = 0; i < LinhasTotais; i++)
    {
        for (int j = 0; j < ColunasTotais; j++)
            if (j%2 == 0)
            {
                if (IndItemEm(i, j/2, LinhasTotais, Resto) != -1)
                    Label1 += Palavras[IndItemEm(i, j/2, LinhasTotais, Resto)];
                AddEspacoString(&Label1, MatrizEspacosELargura[i][j]);
                AddEspacoString(&Label2, MatrizQtChar[i][j] + MatrizEspacosELargura[i][j]);
            }
            else
            {
                if (IndItemEm(i, j/2, LinhasTotais, Resto) != -1)
                    Label2 += Traducoes[IndItemEm(i, j/2, LinhasTotais, Resto)];
                AddEspacoString(&Label2, MatrizEspacosELargura[i][j]);
                AddEspacoString(&Label1, MatrizQtChar[i][j] + MatrizEspacosELargura[i][j]);
            }
        Label1 += "|\n|";
        Label2 += "|\n|";
    }
    Label1.erase(Label1.size() - 1, Label1.size());
    Label2.erase(Label2.size() - 1, Label2.size());
    ui->TextoCor1->setText(QString::fromStdString(Label1));
    ui->TextoCor2->setText(QString::fromStdString(Label2));
}

int ExibeTraducoesRealizadas::IndItemEm(int i, int x, int Alt, int Resto)
{
    int Men = (x - Resto);
    if (Men < 0)
        Men = 0;
    if (i+1 == Alt && x >= Resto)
        return -1;
    return (i + x * Alt) - Men;
}

int ExibeTraducoesRealizadas::QtEspacos(int TamanhoString, int LarguraColuna, int &Sobresalente)
{
    int QtSpc;
    if (TamanhoString + Sobresalente >= LarguraColuna)
    {
        QtSpc = 1;
        Sobresalente = TamanhoString + Sobresalente - LarguraColuna + 1;
    }
    else
    {
        QtSpc = LarguraColuna - (TamanhoString + Sobresalente);
        Sobresalente = 0;
    }
    return QtSpc;
}

void ExibeTraducoesRealizadas::AddEspacoString(string *A, int QtSpc)
{
    for (int c = 0; c < QtSpc; c++)
        A->operator +=(" ");
}

void ExibeTraducoesRealizadas::on_largurasPalavras_valueChanged(int arg1)
{
    LarguraPalavra = arg1;
    if (Editavel)
    {
        Editavel = 0;
        int k = ui->QtColunas->value();
        ui->QtColunas->setValue(0);
        Editavel = 1;
        ui->QtColunas->setValue(k);
    }
}

void ExibeTraducoesRealizadas::on_largurasTraducoes_valueChanged(int arg1)
{
    LarguraTraducao = arg1;
    if (Editavel)
    {
        Editavel = 0;
        int k = ui->QtColunas->value();
        ui->QtColunas->setValue(0);
        Editavel = 1;
        ui->QtColunas->setValue(k);
    }
}
