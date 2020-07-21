#include "praticar.h"
#include "ui_praticar.h"

Praticar::Praticar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Praticar)
{
    ui->setupUi(this);
}

Praticar::~Praticar()
{
    delete ui;
}
