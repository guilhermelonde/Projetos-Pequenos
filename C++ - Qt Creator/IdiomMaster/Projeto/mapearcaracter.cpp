#include "mapearcaracter.h"
#include "ui_mapearcaracter.h"

MapearCaracter::MapearCaracter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapearCaracter)
{
    ui->setupUi(this);
    this->setWindowTitle("");
}

MapearCaracter::~MapearCaracter()
{
    delete ui;
}

void MapearCaracter::Parametro(string A, string *B, bool *Mapeou)
{
    ui->caracter->setText(QString::fromStdString(A));
    Str = B;
    Mp = Mapeou;
    *Mp = 0;
}

void MapearCaracter::on_ok_pressed()
{
    string S = ui->chave->text().toStdString();
    if (S != "")
    {
        *Str = S;
        *Mp = 1;
    }
    this->close();
}

void MapearCaracter::on_cancela_pressed()
{
    this->close();
}
