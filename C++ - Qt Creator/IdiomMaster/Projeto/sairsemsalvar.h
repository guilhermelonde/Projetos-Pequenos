#ifndef SAIRSEMSALVAR_H
#define SAIRSEMSALVAR_H

#include <QDialog>

namespace Ui {
class SairSemSalvar;
}

class SairSemSalvar : public QDialog
{
    Q_OBJECT

public:
    explicit SairSemSalvar(QWidget *parent = 0);
    ~SairSemSalvar();
    void Parametro(int *I);

private slots:
    void on_cancelar_pressed();
    void on_sim_pressed();
    void on_nao_pressed();

private:
    Ui::SairSemSalvar *ui;
    int *Fc;
};

#endif // SAIRSEMSALVAR_H
