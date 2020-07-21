#ifndef ABRIRROTINADEARQUIVO_H
#define ABRIRROTINADEARQUIVO_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class AbrirRotinaDeArquivo;
}

class AbrirRotinaDeArquivo : public QDialog
{
    Q_OBJECT

public:
    explicit AbrirRotinaDeArquivo(QWidget *parent = 0);
    ~AbrirRotinaDeArquivo();
    void Parametro(int *Func, string Text, string Text1);

private slots:
    void on_iniciar_pressed();
    void on_continuar_pressed();

private:
    Ui::AbrirRotinaDeArquivo *ui;
    int *Func;
};

#endif // ABRIRROTINADEARQUIVO_H
