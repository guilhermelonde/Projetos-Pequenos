#ifndef MODOEDICAO_H
#define MODOEDICAO_H

#include <QDialog>
#include <QCloseEvent>
#include <QWidget>
#include <QResizeEvent>
#include "dicionario.h"
#include "mapateclado.h"
#include "entrardicionario.h"
//#include "editagerais.h"

namespace Ui {
class ModoEdicao;
}

class ModoEdicao : public QDialog
{
    Q_OBJECT

public:
    explicit ModoEdicao(QWidget *parent = 0);
    ~ModoEdicao();
    void Parametro(Dicionario *D);

private slots:
    void on_salvar_pressed();
    void on_configuraTeclado_pressed();
    void on_modoListaSelecionadas_pressed();
    void on_irUltimaTraduzida_pressed();

private:
    Ui::ModoEdicao *ui;
    Dicionario *Dic;
    MapaTeclado MT;
    int Alteracoes;
    JanelasEdicao *tela;
    EntrarDicionario *ED;
    int PrimeiraTraduzida, UltimaTraduzida;
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent * event);
};

#endif // MODOEDICAO_H
