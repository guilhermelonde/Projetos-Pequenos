#ifndef CAIXAOPCOESPRATICAR_H
#define CAIXAOPCOESPRATICAR_H

#include <QWidget>
#include "mapateclado.h"

namespace Ui {
class CaixaOpcoesPraticar;
}

class CaixaOpcoesPraticar : public QWidget
{
    Q_OBJECT

public:
    explicit CaixaOpcoesPraticar(QWidget *parent = 0);
    ~CaixaOpcoesPraticar();
    void Parametro(MapaTeclado *MP);

private slots:
    void on_pushButton_pressed();

private:
    Ui::CaixaOpcoesPraticar *ui;
    MapaTeclado *MPT;
};

#endif // CAIXAOPCOESPRATICAR_H
