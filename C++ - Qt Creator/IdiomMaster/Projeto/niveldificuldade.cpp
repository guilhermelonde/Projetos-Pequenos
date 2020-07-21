#include "niveldificuldade.h"
#include "ui_niveldificuldade.h"

NivelDificuldade::NivelDificuldade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NivelDificuldade)
{
    ui->setupUi(this);
    setWindowTitle(" ");
}

NivelDificuldade::~NivelDificuldade()
{
    delete ui;
}

void NivelDificuldade::Parametro(int *nivel)
{
    NivelDif = nivel;
}

void NivelDificuldade::on_ok_pressed()
{
    if (ui->facil->isChecked())
        *NivelDif = 1;
    if (ui->medio->isChecked())
        *NivelDif = 2;
    if (ui->dificil->isChecked())
        *NivelDif = 3;
    this->close();
}
