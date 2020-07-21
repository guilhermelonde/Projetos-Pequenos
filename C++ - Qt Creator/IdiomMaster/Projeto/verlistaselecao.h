#ifndef VERLISTASELECAO_H
#define VERLISTASELECAO_H

#include <QDialog>
#include <vector>
#include <dicionario.h>
#include <pratica.h>

namespace Ui {
class VerListaSelecao;
}

class VerListaSelecao : public QDialog
{
    Q_OBJECT

public:
    explicit VerListaSelecao(QWidget *parent = 0);
    ~VerListaSelecao();
    void Parametro(Dicionario *D, Pratica *P, vector <QString> &A, vector <QString> &B, int Nivel, bool *podeExecutar);

private slots:
    void on_tabela_itemSelectionChanged();
    void on_incluirlinhas_pressed();
    void on_excluirlinhas_pressed();
    void on_incluirtodas_pressed();
    void on_excluirtodas_pressed();
    void on_irparalinha_clicked();
    void on_irparalinha_2_pressed();
    void on_irselecionar_pressed();
    void on_pronto_pressed();
    void on_irbuscarorigem_pressed();
    void on_irbuscartraducao_pressed();
    void on_linhaIrPara_editingFinished();
    void on_linhabuscapalavra_editingFinished();
    void on_linhabuscatraducao_editingFinished();
    void on_selecionarPalavras_editingFinished();

private:
    int incluidas;
    Ui::VerListaSelecao *ui;
    Dicionario *Dic;
    vector <QString> *Va;
    vector <QString> *Vb;
    Pratica *Pra;
    int N;
    bool *PE;
    enum coluna{ORIGEM, TRADU, PRATI};
};

#endif // VERLISTASELECAO_H
