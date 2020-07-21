#ifndef VERLISTA_H
#define VERLISTA_H

#include <QDialog>
#include <dicionario.h>

namespace Ui {
class VerLista;
}

class VerLista : public QDialog
{
    Q_OBJECT

public:
    explicit VerLista(QWidget *parent = 0);
    ~VerLista();
    void Mostrar (Dicionario *D);

private slots:
    void on_ok_pressed();
    void on_pesquisar_pressed();

private:
    Ui::VerLista *ui;
    Dicionario *Dic;
    enum coluna {ORIGEM, TRADU, PRATI};
    void resizeEvent(QResizeEvent * event);
};

#endif // VERLISTA_H
