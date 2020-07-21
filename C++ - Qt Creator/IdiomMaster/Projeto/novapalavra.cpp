#include "novapalavra.h"
#include "ui_novapalavra.h"

NovaPalavra::NovaPalavra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovaPalavra)
{
    ui->setupUi(this);
    setWindowTitle("Nova palavra");
}

NovaPalavra::~NovaPalavra()
{
    delete ui;
}

void NovaPalavra::Parametro(QString *Nova)
{
    this->Nova = Nova;
}

void NovaPalavra::on_linha_editingFinished()
{
    ui->ok->setFocus();
}

void NovaPalavra::on_ok_pressed()
{
    *Nova = ui->linha->text();
    this->close();
}
