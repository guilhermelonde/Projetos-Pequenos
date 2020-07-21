#ifndef NIVEL_H
#define NIVEL_H

#include <QDialog>

namespace Ui {
class Nivel;
}

class Nivel : public QDialog
{
    Q_OBJECT

public:
    explicit Nivel(QWidget *parent = 0);
    ~Nivel();
    void parametroNivel(int *nivel);

private slots:
    void on_cancelar_pressed();
    void on_ok_pressed();

private:
    Ui::Nivel *ui;
    int *nivel;
};

#endif // NIVEL_H
