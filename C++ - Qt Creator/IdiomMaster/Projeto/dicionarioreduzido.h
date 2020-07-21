#ifndef DICIONARIOREDUZIDO_H
#define DICIONARIOREDUZIDO_H

#include <QDialog>
#include <QCloseEvent>
#include <vector>
#include "dicionario.h"

namespace Ui {
class DicionarioReduzido;
}

class DicionarioReduzido : public QDialog
{
    Q_OBJECT

public:
    explicit DicionarioReduzido(QWidget *parent = 0);
    ~DicionarioReduzido();
    int Parametro(QString filename, Dicionario *Dic);
    void resizeEvent ( QResizeEvent * event );

private slots:
    void on_sim_pressed();
    void on_tabela_itemSelectionChanged();
    void on_nao_pressed();
    void on_tabela_activated(const QModelIndex &index);
    void closeEvent(QCloseEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void on_listar_pressed();

    void on_primeiraDaSequencia_pressed();

private:
    Ui::DicionarioReduzido *ui;
    vector <string> Inseridos;
    QString filename;
    Dicionario *Dic;
    int LinhaAtual, LinhaAtualProv;
    int Modif;
    int PalavrasIncluidas;
    bool EscolhidaPrimeira;
    int mantemMeio;
    enum coluna {STATUS, ORIGEM, TRADU};
    int Importa();
    void SetaInseridos();
    void Insere(string A);
    void Remove(string A);
    inline string getPrimeira(string A);
    inline string getSegunda(string A);
    void Salvar();
    int contaPalavras(string S);
};

#endif // DICIONARIOREDUZIDO_H
