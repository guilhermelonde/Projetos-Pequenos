#include "pratica.h"
#include "ui_pratica.h"
#include <QDesktopWidget>
#include <QTextStream>
#include <cstdlib>
#include <queue>
#include "qstring.h"
#include <QTableWidgetSelectionRange>
#include <QFileDialog>
#include <QStandardPaths>
#include <QGridLayout>
#include "qmessagebox.h"
#include "caixaopcoespraticar.h"
#include "stringfrom.h"
#include <iostream>

using namespace std;

Pratica::Pratica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pratica)
{
    ui->setupUi(this);
    MT.setModal(true);
    MT.setWindowFlags(Qt::Window);
    TelaAtual = 0;
    TelaAtualAtual = 0;
    IndAtual[0] = 0;
    IndAtual[1] = 0;
    Linha[0] = 0;
    Linha[1] = 0;
    Coluna[0] = 0;
    Coluna[1] = 0;
    nivel = 0;
    StrAnterior = 0;
    QTPalavras[0] = 0;
    QTPalavras[1] = 0;
    QTTraduzidas[0] = 0;
    QTTraduzidas[1] = 0;
    KataAutoSetavel = 0;
    inicializavel = 1;
    ui->tela1->setChecked(true);
    checado = 0;
    srand(time(0));
}

Pratica::~Pratica()
{
    if (QTTraduzidas[0] + QTTraduzidas[1] == QTPalavras[0] + QTPalavras[1])
    {
        for (int i = 0; i < (int)refDicionario.size(); i++)
            Dic->Praticada[refDicionario[i]] = 1;
        Dic->Exportar();
    }
    delete ui;
}

void Pratica::Parametro(string Langfrom, string Langto, int nivel, Dicionario *Dic)
{
    this->Dic = Dic;
    Lf = Langfrom;
    Lt = Langto;
    nivel += 4;
    this->nivel = nivel;
    MT.Inicializa(Lt);
    vector <string> A;
    StringFrom::InverteOrdemVetor(A, Src[0], Lt);
    TelaAtual = 1;
    for (int i = 0; i < A.size(); i++)
        setLinha(A[i], A[i]);
    TelaAtual = 0;
    KataAutoSetavel = 1;
}

void Pratica::rodar()
{
    int y = TelaAtual, z = TelaAtualAtual;
    for (TelaAtual = 0; KataAutoSetavel && TelaAtual < 2; TelaAtual++)
    {
        TelaAtualAtual = TelaAtual;
        for (int i = 0; i < List[TelaAtual].size(); i++)
            ListInd[TelaAtual].push_back(i);
        for (int i = 0; ListInd[TelaAtual].size() > 0 && i < nivel; i++)
            inserirKata();
    }
    KataAutoSetavel = 0;
    TelaAtual = y;
    int altura = List[TelaAtual].size();
    int altura2 = altura/2;
    if (altura%2 == 1)
        altura2++;

    while (ui->tabela->rowCount() != 0)
        ui->tabela->removeRow(0);
    for (int i = 0; i < altura2; i++)
    {
        ui->tabela->insertRow(i);
        ui->tabela->setItem(i, ORIGEM, new QTableWidgetItem(QString::fromStdString(getPrimeira(List[TelaAtual][i]))));
        ui->tabela->setItem(i, TRADU, new QTableWidgetItem(QString::fromStdString(getSegunda(List[TelaAtual][i]))));
    }
    for (int i = 0; i+altura2 < List[TelaAtual].size(); i++)
    {
        ui->tabela->setItem(i, ORIGEM2, new QTableWidgetItem(QString::fromStdString(getPrimeira(List[TelaAtual][i+altura2]))));
        ui->tabela->setItem(i, TRADU2, new QTableWidgetItem(QString::fromStdString(getSegunda(List[TelaAtual][i+altura2]))));
    }
    y = IndAtual[TelaAtual];
    TelaAtualAtual = TelaAtual;
    for (IndAtual[TelaAtual] = 0; IndAtual[TelaAtual] < altura; IndAtual[TelaAtual]++)
    {
        if (SetarEliminadas[TelaAtual][IndAtual[TelaAtual]] == 1)
            estiloTraduzido();
        if (TelaAtual == TelaAtualAtual && SetarEliminadas[TelaAtual][IndAtual[TelaAtual]] == 2)
            estiloTraduzir(IndAtual[TelaAtual]);
    }
    IndAtual[TelaAtual] = y;
    TelaAtualAtual = z;
    if (inicializavel)
    {
        AtualizaInfo();
        if (KataInd[TelaAtual].size())
            estiloTraduzir(getPalavraKata());
        ui->proximo->setEnabled(false);
    }
}

void Pratica::setLinha(string Lista, string Origem)
{
    QTPalavras[TelaAtual] += contaPalavras(getSegunda(Origem));
    List[TelaAtual].push_back(Lista);
    Src[TelaAtual].push_back(Origem);
    SetarEliminadas[TelaAtual].push_back(0);
}

void Pratica::setRefDicionario(int idxDicionario)
{
    refDicionario.push_back(idxDicionario);
}

inline string Pratica::getPrimeira(string A)
{
    int fn = A.find('\t');
    return A.substr(0, fn + 1);
}

inline string Pratica::getSegunda(string A)
{
    int fn = -1, fn2;
    do
    {
        fn = A.find('\t', fn+1);
        fn2 = A.find('\t', fn+1);
    }while (fn2 != string::npos);
    return A.substr(fn+1, A.size() - 1);
}

void Pratica::setSegunda(string A)
{
    string Ant = getPrimeira(List[TelaAtualAtual][IndAtual[TelaAtualAtual]]);
    Ant = Ant + "\t" + A;
    List[TelaAtualAtual][IndAtual[TelaAtualAtual]] = Ant;
}

void Pratica::inserirKata()
{
    int k = rand() % ListInd[TelaAtualAtual].size();
    int Ind = ListInd[TelaAtualAtual][k];
    ListInd[TelaAtualAtual].erase(ListInd[TelaAtualAtual].begin() + k);
    Kt MyKt;
    MyKt.Indice = Ind;
    MyKt.TempoRestante = 0;

    int p = rand() % (KataInd[TelaAtualAtual].size() + 1);

    KataInd[TelaAtualAtual].push_back(MyKt);
    for (int i = KataInd[TelaAtualAtual].size() - 1; i > p; i--)
        KataInd[TelaAtualAtual][i] = KataInd[TelaAtualAtual][i - 1];
    KataInd[TelaAtualAtual][p] = MyKt;
}

void Pratica::submetePalavra(string Palavra)
{
    int u = PalavraSubstring(Palavra);
    QString Texto;
    if (u == 0)
    {
        SetarEliminadas[TelaAtualAtual][IndAtual[TelaAtualAtual]] = 0;
        ui->status->setStyleSheet("QLabel { color : red; }");
        Texto = "Incorreto! Respostas corretas: " + QString::fromStdString(getSegunda(List[TelaAtualAtual][IndAtual[TelaAtualAtual]]));
        if (inicializavel)
            estiloTraduzindo();
    }
    if (u == 1)
    {
        SetarEliminadas[TelaAtualAtual][IndAtual[TelaAtualAtual]] = 0;
        ui->status->setStyleSheet("QLabel { color : green; }");
        Texto = "Correto! Ainda resta traduzir: " + QString::fromStdString(getSegunda(List[TelaAtualAtual][IndAtual[TelaAtualAtual]]));
        if (inicializavel)
            estiloTraduzindo();
    }
    if (u == 2)
    {
        SetarEliminadas[TelaAtualAtual][IndAtual[TelaAtualAtual]] = 1;
        ui->status->setStyleSheet("QLabel { color : blue; }");
        Texto = "Correto! palavra eliminada";

        estiloTraduzido();
        setPalavraKata();
    }
    AtualizaInfo();
    ui->status->setText(Texto);
    if (KataInd[0].size() + KataInd[1].size() == 0)
        QMessageBox::information(0," ","Todas as palavras foram traduzidas!");
}

int Pratica::getPalavraKata()
{
    if (!KataInd[TelaAtualAtual].size())
        return -1;
    QString Texto = "Traduza: ";
    int p;
    do
    {
        p = rand() % KataInd[TelaAtualAtual].size();
    } while (KataInd[TelaAtualAtual][p].TempoRestante != 0);
    string Palavra = getPrimeira(List[TelaAtualAtual][KataInd[TelaAtualAtual][p].Indice]);
    if (Palavra[0] == '\n' || Palavra[0] == '\r')
        Palavra = Palavra.substr(1, Palavra.size());
    Texto += QString::fromStdString(Palavra);
    ui->traduza->setText(Texto);
    return KataInd[TelaAtualAtual][p].Indice;
}

void Pratica::setPalavraKata()
{
    int i;
    for (i = 0; i < KataInd[TelaAtualAtual].size(); i++)
        if (KataInd[TelaAtualAtual][i].Indice == IndAtual[TelaAtualAtual])
            break;
    KataInd[TelaAtualAtual].erase(KataInd[TelaAtualAtual].begin() + i);
    if (ListInd[TelaAtualAtual].size())
        inserirKata();
    else
        ConfiguraTempoKata(-1);
}

void Pratica::estiloTraduzir(int Ind)
{
    if (TelaAtual != TelaAtualAtual)
        return;
    IndAtual[TelaAtual] = Ind;
    SetarEliminadas[TelaAtual][IndAtual[TelaAtual]] = 2;
    selecionaRow(IndAtual[TelaAtual], 1);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual])->setBackgroundColor(Qt::white);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setBackgroundColor(Qt::white);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setText(" ");
}

void Pratica::estiloTraduzindo()
{
    if (TelaAtual != TelaAtualAtual)
        return;
    selecionaRow(IndAtual[TelaAtual], 0);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual])->setBackgroundColor(Qt::transparent);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setBackgroundColor(Qt::transparent);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setText(QString::fromStdString(getSegunda(List[TelaAtual][IndAtual[TelaAtual]])));
}

void Pratica::estiloTraduzido()
{
    if (TelaAtual != TelaAtualAtual)
        return;
    SetarEliminadas[TelaAtual][IndAtual[TelaAtual]] = 1;
    selecionaRow(IndAtual[TelaAtual], 1);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual])->setBackgroundColor(Qt::transparent);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual])->setTextColor(Qt::gray);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setBackgroundColor(Qt::transparent);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setTextColor(Qt::gray);
    ui->tabela->item(Linha[TelaAtual], Coluna[TelaAtual] + 1)->setText(QString::fromStdString(getSegunda(Src[TelaAtual][IndAtual[TelaAtual]])));
}

void Pratica::selecionaRow(int Ind, bool M)
{
    int altura = List[TelaAtualAtual].size();
    int altura2 = altura/2;
    if (altura%2 == 1)
        altura2++;
    int k = 0;
    if (Ind >= altura2)
        k = 2;
    Ind = Ind % altura2;
    if (M)
        ui->tabela->selectRow(Ind);
    ui->tabela->clearSelection();
    QTableWidgetSelectionRange SR(Ind, k, Ind, k + 1);
    ui->tabela->setRangeSelected(SR, true);
    Linha[TelaAtualAtual] = Ind;
    Coluna[TelaAtualAtual] = k;
}

int Pratica::PalavraSubstring(string A)
{
    ConfiguraTempoKata(IndAtual[TelaAtualAtual]);
    string B = getSegunda(List[TelaAtualAtual][IndAtual[TelaAtualAtual]]);
    bool existe = StringFrom::PalavrasSubstring(A, B, Lt, 1, QTTraduzidas[TelaAtualAtual]);
    setSegunda(B);
    if (B.size() == 0)
        return 2;
    if (existe)
        return 1;
    string C = getSegunda(Src[TelaAtualAtual][IndAtual[TelaAtualAtual]]);
    return StringFrom::PalavrasSubstring(A, C, Lt, 0, QTTraduzidas[TelaAtualAtual]);
}

void Pratica::ConfiguraTempoKata(int Ind)
{
    int kata = KataInd[TelaAtualAtual].size() - 2;
    if (kata < 0)
        kata = 0;
    for (int i = 0; i < KataInd[TelaAtualAtual].size(); i++)
    {
        if (KataInd[TelaAtualAtual][i].TempoRestante != 0)
            KataInd[TelaAtualAtual][i].TempoRestante--;
        if (KataInd[TelaAtualAtual][i].Indice == Ind)
            KataInd[TelaAtualAtual][i].TempoRestante = kata;
    }
}

int Pratica::contaPalavras(string S)
{
    if (S == "")
        return 0;
    int i, pos = 0;
    for (i = 1; S.find(";", pos) != string::npos; i++)
    {
        int p = S.find(';', pos);
        if (p - pos == 1)
            i--;
        pos = p + 1;
    }
    return i;
}

void Pratica::resizeEvent(QResizeEvent * event)
{
    int largura = this->width() - 40;
    int larguraA = (largura*15/100) - 5;
    int larguraB = (largura*35/100) - 5;
    ui->tabela->setColumnWidth(0, larguraA);
    ui->tabela->setColumnWidth(1, larguraB);
    ui->tabela->setColumnWidth(2, larguraA);
    ui->tabela->setColumnWidth(3, larguraB);
}

void Pratica::DesabilitaOuHabilitaJanela()
{
    if (KataInd[TelaAtual].size() == 0)
    {
        ui->traduza->setText("");
        ui->proximo->setEnabled(false);
        ui->submeter->setEnabled(false);
        if (TelaAtualAtual == 1)
        {
            TelaAtual = 0;
            TelaAtualAtual = 0;
        }
        else
        {
            TelaAtual = 1;
            TelaAtualAtual = 1;
        }
    }
    else
    {
        if (KataInd[TelaAtualAtual].size() != 0 && ui->traduza->text() == "")
            estiloTraduzir(getPalavraKata());
        ui->proximo->setEnabled(false);
        ui->PalavraASubmeter->setFocus();
        ui->submeter->setEnabled(true);
    }
}

void Pratica::AtualizaInfo()
{
    ui->EliminadasDir->setText("Eliminadas em " + QString::fromStdString(Lf + "-" + Lt + ": ") + QString::number(QTTraduzidas[0]) + " de " + QString::number(QTPalavras[0]));
    ui->EliminadaRev->setText("Eliminadas em " + QString::fromStdString(Lt + "-" + Lf + ": ") + QString::number(QTTraduzidas[1]) + " de " + QString::number(QTPalavras[1]));
    ui->ElimTotal->setText("Eliminadas no total: " + QString::number(QTTraduzidas[0] + QTTraduzidas[1]) + " de " + QString::number(QTPalavras[0] + QTPalavras[1]));
    ui->barraProgresso->setValue(((float)(QTTraduzidas[0] + QTTraduzidas[1]) / (float)(QTPalavras[0] + QTPalavras[1]))*100);
}

void Pratica::on_proximo_pressed()
{
    if (checado == 1 && TelaAtual == 0)
        TelaAtual = 1;
    if (checado == 0 && TelaAtual == 1)
        TelaAtual = 0;
    ui->traduza->setText("");
    TelaAtualAtual = TelaAtual;
    inicializavel = 1;
    ui->PalavraASubmeter->setText("");
    ui->status->setText("");
    int z = getPalavraKata();
    if (z != -1)
        estiloTraduzir(z);
    DesabilitaOuHabilitaJanela();
}

void Pratica::on_submeter_pressed()
{
    submetePalavra(ui->PalavraASubmeter->text().toStdString());
    ui->submeter->setEnabled(false);
    ui->proximo->setEnabled(true);
    ui->proximo->setFocus();
    StrAnterior = 0;
}

void Pratica::on_opcoes_pressed()
{
    QRect QR = ui->opcoes->geometry();
    int x, y;
    x = QR.left();
    y = QR.top() + 55;
    QR = this->geometry();
    x += QR.left();
    y += QR.top();
    CaixaOpcoesPraticar *CO = new CaixaOpcoesPraticar (this);
    CO->setGeometry(x, y, 150, 300);
    CO->Parametro(&MT);
    CO->show();
}

void Pratica::on_PalavraASubmeter_textChanged()
{
    if (TelaAtualAtual == 1)
        return;
    string ultm = ui->PalavraASubmeter->text().toStdString(), Nova;
    if (ultm.size() != 0 && StrAnterior <= ultm.size())
    {
        string chave = ultm.substr(StrAnterior, ultm.size());
        int x = this->geometry().left(), y = this->geometry().top();
        x = x + ui->PalavraASubmeter->geometry().left() + ui->PalavraASubmeter->cursorPosition();
        y = y + ui->PalavraASubmeter->geometry().top() + 30;
        if (MT.listaDeOpcoes(chave, x, y))
        {
            Nova = ultm.substr(0, StrAnterior) + MT.getElemento();
            ui->PalavraASubmeter->setText(QString::fromStdString(Nova));
            ui->PalavraASubmeter->cursorWordForward(true);
            StrAnterior = Nova.size();
        }
        else
            StrAnterior = ultm.size();
        if (StrAnterior < 0)
            StrAnterior = 0;
    }
    else
        StrAnterior = ultm.size();
}

void Pratica::on_PalavraASubmeter_editingFinished()
{
    ui->submeter->setFocus();
}

void Pratica::on_tela1_clicked()
{
    if (checado != 0)
    {
        inicializavel = 0;
        TelaAtual = 0;
        rodar();
    }
    if (!ui->proximo->isEnabled())
        DesabilitaOuHabilitaJanela();
    inicializavel = 1;
    checado = 0;
}

void Pratica::on_tela2_clicked()
{
    if (checado != 1)
    {
        inicializavel = 0;
        TelaAtual = 1;
        rodar();
    }
    if (!ui->proximo->isEnabled())
        DesabilitaOuHabilitaJanela();
    inicializavel = 1;
    checado = 1;
}
