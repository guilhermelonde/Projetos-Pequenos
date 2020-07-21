#include "dicionarioreduzido.h"
#include "ui_dicionarioreduzido.h"
#include "iostream"
#include "string"
#include "QTextStream"
#include "stringfrom.h"
#include "exibetraducoesrealizadas.h"

DicionarioReduzido::DicionarioReduzido(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DicionarioReduzido)
{
    ui->setupUi(this);
    ui->sim->setEnabled(false);
    ui->nao->setEnabled(false);
    LinhaAtual = -1;
    ui->labelIncluir->setText("Selecione a primeira linha para começar a selecionar as palavras em sequência");
    ui->labelIncluidas->setText("Palavras incluídas: 0");
    PalavrasIncluidas = 0;
    EscolhidaPrimeira = 0;
    Modif = 0;
}

DicionarioReduzido::~DicionarioReduzido()
{
    delete ui;
}

int DicionarioReduzido::Parametro(QString filename, Dicionario *Dic)
{
    this->filename = filename;
    this->Dic = Dic;
    int v = Importa();
    if (v)
        return v;
    int tabk = 0;
    for (int i = 0; i < Dic->getUltimaTrad(); i++)
    {
        string A = Dic->getPrimeira(i);
        while (A[0] == 10)
            A.erase(0, 1);
        while (A[A.size() - 1] == '\t')
            A = A.substr(0, A.size() - 1);
        string B = Dic->getSegunda(i);
        for (unsigned long long u = 0; u != string::npos; u = B.find(";", u + 1))
        {
            string C = B.substr(u, B.find(";", u + 1) - u);
            while (C[0] == ' ' || C[0] == ';')
                C.erase(0, 1);
            ui->tabela->insertRow(tabk);
            ui->tabela->setItem(tabk, STATUS, new QTableWidgetItem(""));
            ui->tabela->setItem(tabk, ORIGEM, new QTableWidgetItem(QString::fromStdString(A)));
            ui->tabela->setItem(tabk, TRADU, new QTableWidgetItem(QString::fromStdString(C)));
            tabk++;
        }
    }
    SetaInseridos();
    ui->labelIncluidas->setText("Palavras incluídas: " + QString::number(Inseridos.size()) + "    Traduções incluídas: " + QString::number(PalavrasIncluidas));
    return 0;
}

void DicionarioReduzido::resizeEvent ( QResizeEvent * event )
{
    int ws = ui->tabela->width();
    mantemMeio = ui->tabela->height() / 2;
    mantemMeio = mantemMeio / 25;
    ui->tabela->setColumnWidth(0, (float)ws * 0.20);
    ui->tabela->setColumnWidth(1, (float)ws * 0.40);
    ui->tabela->setColumnWidth(2, (float)ws * 0.40 - 20);
}

void DicionarioReduzido::on_sim_pressed()
{
    if (ui->tabela->item(LinhaAtualProv, 0)->text() != "incluído")
    {
        char lf = 10;
        PalavrasIncluidas++;
        Insere(lf + (ui->tabela->item(LinhaAtualProv, 1)->text() + "\t" + ui->tabela->item(LinhaAtualProv, 2)->text()).toStdString());
    }
    ui->tabela->item(LinhaAtualProv, 0)->setText("incluído");
    ui->tabela->item(LinhaAtualProv, 0)->setTextColor(Qt::green);
    if (LinhaAtualProv == LinhaAtual)
        LinhaAtual++;
    ui->tabela->selectRow(LinhaAtual);
    ui->labelIncluidas->setText("Palavras incluídas: " + QString::number(Inseridos.size()) + "    Traduções incluídas: " + QString::number(PalavrasIncluidas));
    Modif = (Modif + 1) % 10;
    if (!Modif)
        Salvar();
}

void DicionarioReduzido::on_tabela_itemSelectionChanged()
{
    if (EscolhidaPrimeira)
    {
        int row = ui->tabela->currentRow();
        if (LinhaAtual == -1 || (LinhaAtual == row))
            LinhaAtual = row;
        LinhaAtualProv = row;
        EscolhidaPrimeira = 0;
        ui->tabela->selectRow(row - mantemMeio);
        ui->tabela->selectRow(row + mantemMeio);
        ui->tabela->selectRow(row);
        EscolhidaPrimeira = 1;
        ui->labelIncluir->setText("Incluir: " + ui->tabela->item(LinhaAtualProv, 1)->text() + "             " + ui->tabela->item(LinhaAtualProv, 2)->text());
    }
}

void DicionarioReduzido::on_nao_pressed()
{
    if (ui->tabela->item(LinhaAtualProv, 0)->text() == "incluído")
    {
        char lf = 10;
        PalavrasIncluidas--;
        Remove(lf + (ui->tabela->item(LinhaAtualProv, 1)->text() + "\t" + ui->tabela->item(LinhaAtualProv, 2)->text()).toStdString());
    }
    ui->tabela->item(LinhaAtualProv, 0)->setText("ignorado");
    ui->tabela->item(LinhaAtualProv, 0)->setTextColor(Qt::red);
    if (LinhaAtualProv == LinhaAtual)
        LinhaAtual++;
    ui->tabela->selectRow(LinhaAtual);
    ui->labelIncluidas->setText("Palavras incluídas: " + QString::number(Inseridos.size()) + "    Traduções incluídas: " + QString::number(PalavrasIncluidas));
    Modif = (Modif + 1) % 10;
    if (!Modif)
        Salvar();
}

void DicionarioReduzido::on_tabela_activated(const QModelIndex &index)
{
    if (!EscolhidaPrimeira)
    {
        EscolhidaPrimeira = 1;
        ui->sim->setEnabled(true);
        ui->nao->setEnabled(true);
        LinhaAtual = index.row();
        LinhaAtualProv = index.row();
        ui->tabela->selectRow(LinhaAtualProv);
        ui->labelIncluir->setText("Incluir: " + ui->tabela->item(LinhaAtualProv, 1)->text() + "             " + ui->tabela->item(LinhaAtualProv, 2)->text());
    }
}

void DicionarioReduzido::closeEvent(QCloseEvent * event)
{
    Salvar();
    event->accept();
}

void DicionarioReduzido::keyPressEvent(QKeyEvent *event)
{
    if (event->text() == "s" || event->text() == "y")
        this->on_sim_pressed();
    if (event->text() == "n")
        this->on_nao_pressed();
}

int DicionarioReduzido::Importa()
{
    QFile Arq(filename);
    Arq.open(QIODevice::ReadOnly);
    if (Arq.isOpen())
    {
        QByteArray QBA = Arq.readAll();
        string QBA_Str = QBA.toStdString(), A, Source, For, Aux = QBA_Str.substr(0, 31);
        if (Aux == "//IdiomMaster_Translations_File")
        {
            QBA_Str.erase(0, 35);
            Source = QBA_Str.substr(0, 2);
            if (Dic->getSrc() != Source || !StringFrom::IdiomaValido(Source))
                return 2;
            QBA_Str.erase(0, 5);
            For = QBA_Str.substr(0, 2);
            if (Dic->getFor() != For || !StringFrom::IdiomaValido(For))
                return 3;
            QBA_Str.erase(0, 4);
            StringFrom::Converte(Source, For, QBA_Str, A);
            for (int i = 0; i < A.size(); i++)
            {
                string Palavra;
                int j;
                for (j = 0; A[i] != 13 && i < A.size(); j++)
                    Palavra += A[i++];
                if (Palavra.find("\t") != string::npos)
                {
                    Inseridos.push_back(Palavra);
                    PalavrasIncluidas += contaPalavras(getSegunda(Palavra));
                }
            }
        }
        else
            return 1;
    }
    return 0;
}

void DicionarioReduzido::SetaInseridos()
{
    int k = 0;
    bool rem = 0;
    for (int i = 0; i < ui->tabela->rowCount() && k < Inseridos.size(); i++)
    {
        string A = ui->tabela->item(i, 1)->text().toStdString();
        string B = getPrimeira(Inseridos[k]);
        while (A[0] == 10)
            A.erase(0, 1);
        while (B[0] == 10)
            B.erase(0, 1);
        while (B[B.size() - 1] == '\t')
            B.erase(B.begin() + B.size() - 1);
        int u = StringFrom::ComparaStrings(A, B, Dic->getSrc());
        if (u >= 0)
            if (u == 1)
            {
                k++;
                i--;
            }
            else
            {
                string C = getSegunda(Inseridos[k]);
                if (StringFrom::ESubstring(ui->tabela->item(i, 2)->text().toStdString(), C, 0, Dic->getFor()))
                {
                    ui->tabela->item(i, 0)->setText("incluído");
                    ui->tabela->item(i, 0)->setTextColor(Qt::yellow);
                }
            }
        if (i < ui->tabela->rowCount() - 1)
        {
            string D = ui->tabela->item(i + 1, 1)->text().toStdString();
            while (D[0] == 10)
                D.erase(0, 1);
            if (StringFrom::ComparaStrings(A, D, Dic->getSrc()) == 1)
                k = 0;
        }
    }
}

void DicionarioReduzido::Insere(string A)
{
    string U = getPrimeira(A), U_2 = getSegunda(A);
    int i = Inseridos.size();
    Inseridos.push_back(A);
    while (i > 0 && StringFrom::ComparaStrings(getPrimeira(Inseridos[i]), getPrimeira(Inseridos[i - 1]), Dic->getSrc()) < 0)
    {
        string troca = Inseridos[i];
        Inseridos[i] = Inseridos[i - 1];
        Inseridos[i - 1] = troca;
        i--;
    }
    if (i > 0 && StringFrom::ComparaStrings(getPrimeira(Inseridos[i]), getPrimeira(Inseridos[i - 1]), Dic->getSrc()) == 0)
    {
        Inseridos.erase(Inseridos.begin() + i);
        i--;
        string B = getSegunda(Inseridos[i]);
        if (!StringFrom::ESubstring(U_2, B, 0, Dic->getFor()))
            Inseridos[i] = Inseridos[i] + "; " + U_2;
    }
}

void DicionarioReduzido::Remove(string A)
{
    string U = getPrimeira(A), U_2 = getSegunda(A);
    int i;
    for (i = Inseridos.size() - 1; i > 0 && StringFrom::ComparaStrings(U, getPrimeira(Inseridos[i]), Dic->getSrc()) < 0; i--);
    if (StringFrom::ComparaStrings(U, getPrimeira(Inseridos[i]), Dic->getSrc()) == 0)
    {
        string B = getSegunda(Inseridos[i]);
        StringFrom::ESubstring(U_2, B, 1, Dic->getFor());
        if (B == "")
            Inseridos.erase(Inseridos.begin() + i);
        else
            Inseridos[i] = getPrimeira(Inseridos[i]) + "\t" + B;
    }
}

string DicionarioReduzido::getPrimeira(string A)
{
    int u = A.find("\t");
    return A.substr(0, u);
}

string DicionarioReduzido::getSegunda(string A)
{
    int u = A.find("\t");
    while (A.find("\t", u + 1) != string::npos)
        u = A.find("\t", u + 1);
    return A.substr(u + 1, A.size());
}

void DicionarioReduzido::Salvar()
{
    QFile Arq (filename);
    Arq.open(QIODevice::WriteOnly);
    QTextStream streamArquivo(&Arq);
    streamArquivo.setCodec("Latin1");
    streamArquivo << "//IdiomMaster_Translations_File\r\n" << "//" << QString::fromStdString(Dic->getSrc()) << " - " << QString::fromStdString(Dic->getFor()) << "\r\n";
    for (int i = 0; i < Inseridos.size(); i++)
        streamArquivo << StringFrom::ConverteParaAscii(Dic->getSrc(), getPrimeira(Inseridos[i])) << "\t" << StringFrom::ConverteParaAscii(Dic->getFor(), getSegunda(Inseridos[i])) << "\r";
    streamArquivo << "\n$";
    streamArquivo.flush();
    Arq.close();
}

int DicionarioReduzido::contaPalavras(string S)
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

void DicionarioReduzido::on_listar_pressed()
{
    ExibeTraducoesRealizadas ETR;
    ETR.setWindowFlags(Qt::Window);
    ETR.setModal(true);
    for (int i = 0; i < Inseridos.size(); i++)
        ETR.setItem(getPrimeira(Inseridos[i]), Dic->getSrc(), getSegunda(Inseridos[i]), Dic->getFor());
    ETR.Rodar();
    ETR.exec();
}

void DicionarioReduzido::on_primeiraDaSequencia_pressed()
{
    ui->sim->setEnabled(false);
    ui->nao->setEnabled(false);
    LinhaAtual = -1;
    ui->labelIncluir->setText("Selecione a primeira linha para começar a selecionar as palavras em sequência");
    EscolhidaPrimeira = 0;
}
