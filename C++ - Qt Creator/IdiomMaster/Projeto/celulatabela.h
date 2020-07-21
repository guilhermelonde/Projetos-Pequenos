#ifndef CELULATABELA_H
#define CELULATABELA_H

#include <QDialog>
#include "mapateclado.h"

namespace Ui {
class CelulaTabela;
}

class CelulaTabela : public QDialog
{
    Q_OBJECT

public:
    explicit CelulaTabela(QWidget *parent = 0);
    ~CelulaTabela();
    QString *Parametro (QString Texto, MapaTeclado *MT, string Ling);
    QString *Parametro (QString Texto, string Ling);

private slots:
    void on_confirma_pressed();
    void on_linha_editingFinished();
    void on_linha_textChanged();

private:
    Ui::CelulaTabela *ui;
    MapaTeclado *MT;
    QString Saida;
    string Ling;
    bool Editavel;
    int StrAnterior;
    int Estilo;
    void sair();
};

#endif // CELULATABELA_H
