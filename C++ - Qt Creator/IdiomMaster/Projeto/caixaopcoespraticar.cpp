#include "caixaopcoespraticar.h"
#include "ui_caixaopcoespraticar.h"

CaixaOpcoesPraticar::CaixaOpcoesPraticar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaixaOpcoesPraticar)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() | Qt::Popup);
}

CaixaOpcoesPraticar::~CaixaOpcoesPraticar()
{
    delete ui;
}

void CaixaOpcoesPraticar::Parametro(MapaTeclado *MP)
{
    MPT = MP;
}

void CaixaOpcoesPraticar::on_pushButton_pressed()
{
    MPT->exec();
}
