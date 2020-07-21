#include "nivel.h"
#include "ui_nivel.h"

Nivel::Nivel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nivel)
{
    ui->setupUi(this);
    this->setWindowTitle("");
}

Nivel::~Nivel()
{
    delete ui;
}

void Nivel::parametroNivel(int *nivel)
{
    *nivel = 0;
    this->nivel = nivel;
}

void Nivel::on_cancelar_pressed()
{
    this->close();
}

void Nivel::on_ok_pressed()
{
    if (ui->radio3->isChecked())
        *nivel = 3;
    if (ui->radio4->isChecked())
        *nivel = 4;
    if (ui->radio5->isChecked())
        *nivel = 5;
    if (ui->radio6->isChecked())
        *nivel = 6;
    if (ui->radio7->isChecked())
        *nivel = 7;
    this->close();
}
