#include "modoedicao.h"
#include "ui_modoedicao.h"
#include "sairsemsalvar.h"

ModoEdicao::ModoEdicao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModoEdicao)
{
    ui->setupUi(this);
    Alteracoes = 0;
    tela = NULL;
}

ModoEdicao::~ModoEdicao()
{
    delete ui;
}

void ModoEdicao::Parametro(Dicionario *D)
{
    Dic = D;
    MT.Inicializa(Dic->getFor());
    ED = new EntrarDicionario(this);
    ED->Parametro(Dic, &Alteracoes, ui->status, &MT, &PrimeiraTraduzida, &UltimaTraduzida);
    if (tela)
        tela->hide();
    tela = ED;
    tela->show();
    resizeEvent(NULL);
    tela->atualizar();
}

void ModoEdicao::on_salvar_pressed()
{
    Dic->Exportar();
    Alteracoes = 0;
}

void ModoEdicao::on_configuraTeclado_pressed()
{
    MT.exec();
}

void ModoEdicao::closeEvent(QCloseEvent *event)
{
    if (!Alteracoes)
    {
        event->accept();
        return;
    }
    int r;
    SairSemSalvar SSS;
    SSS.setModal(true);
    SSS.Parametro(&r);
    SSS.exec();
    if (r == 1)
        event->ignore();
    if (r == 2)
    {
        Dic->Exportar();
        event->accept();
    }
    if (r == 3)
    {
        Dic->AbrirArquivo();
        event->accept();
    }
}

void ModoEdicao::resizeEvent(QResizeEvent *event)
{
    if (tela)
        tela->setGeometry(71, 42, this->width() - 71, this->height() - 42 - ui->status->height());
}

void ModoEdicao::on_modoListaSelecionadas_pressed()
{
    tela->modoListaSelecionadas();
}

void ModoEdicao::on_irUltimaTraduzida_pressed()
{
    tela->ultimaTraduzida();
}

