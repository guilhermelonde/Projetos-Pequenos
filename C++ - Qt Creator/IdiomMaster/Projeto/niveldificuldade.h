#ifndef NIVELDIFICULDADE_H
#define NIVELDIFICULDADE_H

#include <QDialog>

namespace Ui {
class NivelDificuldade;
}

class NivelDificuldade : public QDialog
{
    Q_OBJECT

public:
    explicit NivelDificuldade(QWidget *parent = 0);
    ~NivelDificuldade();
    void Parametro(int *nivel);

private slots:
    void on_ok_pressed();

private:
    Ui::NivelDificuldade *ui;
    int *NivelDif;
};

#endif // NIVELDIFICULDADE_H
