#ifndef JANELASEDICAO
#define JANELASEDICAO

#include <QDialog>
#include <QLabel>
#include "dicionario.h"
#include "mapateclado.h"

class JanelasEdicao : public QDialog
{
public:
    JanelasEdicao(QWidget *parent = 0) : QDialog(parent) {}
    virtual void modoLista() = 0;
    virtual void modoListaSelecionadas() = 0;
    virtual void ultimaTraduzida() = 0;
    virtual void atualizar() = 0;
    int *Alteracoes;
    QLabel *barraStatus;
    Dicionario *Dic;
    MapaTeclado *MT;
    int *PrimDaSequencia;
    int *UltmDaSequencia;
};

#endif // JANELASEDICAO

