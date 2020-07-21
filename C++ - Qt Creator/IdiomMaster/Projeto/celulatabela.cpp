#include "celulatabela.h"
#include "ui_celulatabela.h"
#include "stringfrom.h"
#include "string"

CelulaTabela::CelulaTabela(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CelulaTabela)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setWindowFlags(windowFlags() | Qt::Popup);
    StrAnterior = 0;
    Editavel = 0;
}

CelulaTabela::~CelulaTabela()
{
    delete ui;
}

QString * CelulaTabela::Parametro (QString Texto, MapaTeclado *MT, string Ling)
{
    this->MT = MT;
    Estilo = 1;
    QRect Sizes = this->geometry();
    ui->linha->setGeometry(0, 0, Sizes.width() - 25, Sizes.height());
    ui->confirma->setGeometry(Sizes.width() - 25, 0, 25, Sizes.height());
    while (Texto.size() > 0 && Texto[0] == 10)
        Texto.remove(0, 1);
    while (Texto.size() > 0 && Texto[Texto.size() - 1] == '\t')
        Texto.remove(Texto.size() - 1, 1);
    StrAnterior = Texto.size();
    ui->linha->setText(Texto);
    ui->linha->setFocus();
    ui->linha->cursorWordForward(true);
    this->Ling = Ling;
    Editavel = 1;
    Saida = ui->linha->text();
    return &Saida;
}

QString * CelulaTabela::Parametro(QString Texto, string Ling)
{
    Estilo = 2;
    QRect Sizes = this->geometry();
    ui->linha->setGeometry(0, 0, Sizes.width() - 25, Sizes.height());
    ui->confirma->setGeometry(Sizes.width() - 25, 0, 25, Sizes.height());
    while (Texto.size() > 0 && Texto[0] == 10)
        Texto.remove(0, 1);
    while (Texto.size() > 0 && Texto[Texto.size() - 1] == '\t')
        Texto.remove(Texto.size() - 1, 1);
    StrAnterior = Texto.size();
    ui->linha->setText(Texto);
    ui->linha->setFocus();
    ui->linha->cursorWordForward(true);
    this->Ling = Ling;
    Editavel = 1;
    Saida = ui->linha->text();
    return &Saida;
}

void CelulaTabela::on_confirma_pressed()
{
    sair();
    this->close();
}

void CelulaTabela::on_linha_editingFinished()
{
    ui->confirma->setFocus();
}

void CelulaTabela::on_linha_textChanged()
{
    if (!Editavel)
        return;
    string ultm = ui->linha->text().toStdString(), Nova;
    if (ultm.size() != 0 && StrAnterior <= ultm.size())
    {
        string chave = ultm.substr(StrAnterior, ultm.size());
        int x = this->geometry().left(), y = this->geometry().top();
        x = x + ui->linha->geometry().left() + ui->linha->cursorPosition();
        y = y + ui->linha->geometry().top() + 30;
        if (Estilo == 1 && MT->listaDeOpcoes(chave, x, y))
        {
            Nova = ultm.substr(0, StrAnterior) + MT->getElemento();
            ui->linha->setText(QString::fromStdString(Nova));
            ui->linha->cursorWordForward(true);
            StrAnterior = Nova.size();
        }
        else if (StringFrom::EProibido(chave, Ling))
            {
                Nova = ultm.substr(0, StrAnterior);
                ui->linha->setText(QString::fromStdString(Nova));
                ui->linha->cursorWordForward(true);
            }
            else
                StrAnterior = ultm.size();
        if (StrAnterior < 0)
            StrAnterior = 0;
    }
    else
        StrAnterior = ultm.size();
}

void CelulaTabela::sair()
{
    string Texto = ui->linha->text().toStdString();
    while (Texto.size() > 0 && StringFrom::NaoPodeEstarNaFrente(Texto.substr(0, 1)))
        Texto.erase(0, 1);
    while (Texto.size() > 1 && StringFrom::NaoPodeEstarAtras(Texto.substr(Texto.size() - 1, Texto.size())))
        Texto.erase(Texto.size() - 1, Texto.size());
    ui->linha->setText(QString::fromStdString(Texto));
    Saida = ui->linha->text();
}
