#ifndef ENTRARDICIONARIO_H
#define ENTRARDICIONARIO_H

#include <QMenu>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <list>
#include <QKeyEvent>
#include "janelasedicao.h"
#include "dicionario.h"
#include "mapateclado.h"

namespace Ui {
class EntrarDicionario;
}

class EntrarDicionario : public JanelasEdicao
{
    Q_OBJECT

public:
    explicit EntrarDicionario(QWidget *parent = 0);
    ~EntrarDicionario();
    void Parametro(Dicionario *D, int *alt, QLabel *s, MapaTeclado *M, int *PrimSequencia, int *UltmSequencia);
    void modoLista();
    void modoListaSelecionadas();
    void ultimaTraduzida();
    void atualizar();

private slots:
    void contextMenuRequested(const QPoint& pos);
    void on_tabela_cellActivated(int row, int column);
    void RemoveLinha();
    void InsereLinha();
    void on_linhaBuscar_editingFinished();
    void on_buscar_pressed();

private:
    Ui::EntrarDicionario *ui;
    QMenu *Menu;
    QAction *Remover;
    QAction *Inserir;
    int larguraA;
    int larguraB;
    int PrimeiraTraduzida;
    list <string> desfazer;
    list <string> refazer;
    enum coluna {ORIGEM, TRADU};
    void consoleDesfazer();
    void consoleRefazer();
    void AlteraItem(int row, int column, QString Texto);
    bool NovoItem(QString Palavra, QString Traducao, int P);
    bool EditaItem(int row, int column);
    void EquacaoPrimUltm(int row, int p);
    void EquacaoPrimUltmRemove(int row);
    void EquacaoPrimUltmAdiciona(int row);
    void resizeEvent(QResizeEvent * event);
};

#endif // ENTRARDICIONARIO_H
