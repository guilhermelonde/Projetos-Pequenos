#ifndef EXIBIR_PROGRESSO_H
#define EXIBIR_PROGRESSO_H

#include <QDialog>
#include <vector>

using namespace std;

struct arquivo
{
    char linha[80];
    int q;
};

namespace Ui {
class Exibir_progresso;
}

class Exibir_progresso : public QDialog
{
    Q_OBJECT

public:
    explicit Exibir_progresso(QWidget *parent = 0);
    ~Exibir_progresso();
    void Exibelista(vector <arquivo> &f);

private:
    Ui::Exibir_progresso *ui;
    enum coluna
    {
        ORIGEM, TRADU
    };
};

#endif // EXIBIR_PROGRESSO_H
