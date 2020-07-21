#ifndef EXIBETRADUCOESREALIZADAS_H
#define EXIBETRADUCOESREALIZADAS_H

#include <QDialog>
#include <string>
#include <vector>

using namespace std;

namespace Ui {
class ExibeTraducoesRealizadas;
}

class ExibeTraducoesRealizadas : public QDialog
{
    Q_OBJECT

public:
    explicit ExibeTraducoesRealizadas(QWidget *parent = 0);
    ~ExibeTraducoesRealizadas();
    void setItem(string Palavra, string Lf, string Traducao, string Lt);
    void Rodar();

private slots:
    void on_QtColunas_valueChanged(int arg1);
    void on_largurasPalavras_valueChanged(int arg1);
    void on_largurasTraducoes_valueChanged(int arg1);

private:
    Ui::ExibeTraducoesRealizadas *ui;
    vector <string> Palavras;
    vector <string> Traducoes;
    vector <int> LargurasPal;
    vector <int> LargurasTrad;
    bool Editavel;
    int LarguraPalavra, LarguraTraducao;
    inline int IndItemEm(int i, int x, int Alt, int Resto);
    inline int QtEspacos(int TamanhoString, int LarguraColuna, int &Sobresalente);
    inline void AddEspacoString(string *A, int QtSpc);
};

#endif // EXIBETRADUCOESREALIZADAS_H
