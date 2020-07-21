#include "sairsemsalvar.h"
#include "ui_sairsemsalvar.h"

SairSemSalvar::SairSemSalvar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SairSemSalvar)
{
    ui->setupUi(this);
    setWindowTitle("");
}

SairSemSalvar::~SairSemSalvar()
{
    delete ui;
}

void SairSemSalvar::Parametro(int *I)
{
    Fc = I;
}

void SairSemSalvar::on_cancelar_pressed()
{
    *Fc = 1;
    this->close();
}

void SairSemSalvar::on_sim_pressed()
{
    *Fc = 2;
    this->close();
}

void SairSemSalvar::on_nao_pressed()
{
    *Fc = 3;
    this->close();
}
