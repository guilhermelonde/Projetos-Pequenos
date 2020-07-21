#ifndef EDITAGERAIS_H
#define EDITAGERAIS_H

#include <QDialog>
#include "janelasedicao.h"

namespace Ui {
class EditaGerais;
}

class EditaGerais : public JanelasEdicao
{
    Q_OBJECT

public:
    explicit EditaGerais(QWidget *parent = 0);
    ~EditaGerais();
    void Parametro(Dicionario *D, int *alt, QLabel *s, MapaTeclado *M, int *PrimSequencia, int *UltmSequencia);
    void modoLista();
    void modoListaSelecionadas();
    void ultimaTraduzida();
    void atualizar();

private slots:
    void on_inverter_pressed();

private:
    Ui::EditaGerais *ui;
    int larguraA, larguraB;
    enum coluna {ORIGEM, TRADU};
    void resizeEvent(QResizeEvent * event);
};

#endif // EDITAGERAIS_H
