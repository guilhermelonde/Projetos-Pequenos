#include "abrirrotinadearquivo.h"
#include "ui_abrirrotinadearquivo.h"

AbrirRotinaDeArquivo::AbrirRotinaDeArquivo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AbrirRotinaDeArquivo)
{
    ui->setupUi(this);
    setWindowTitle(" ");
}

AbrirRotinaDeArquivo::~AbrirRotinaDeArquivo()
{
    delete ui;
}

void AbrirRotinaDeArquivo::Parametro(int *Func, string Text, string Text1)
{
    this->Func = Func;
    ui->texto->setText(QString::fromStdString(Text));
    ui->iniciar->setText(QString::fromStdString(Text1));
}

void AbrirRotinaDeArquivo::on_iniciar_pressed()
{
    *Func = -1;
    this->close();
}

void AbrirRotinaDeArquivo::on_continuar_pressed()
{
    *Func = 1;
    this->close();
}
