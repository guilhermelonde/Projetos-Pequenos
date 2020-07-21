#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_backspace_pressed();
    void on_abreParanteses_pressed();
    void on_fechaParenteses_pressed();
    void on_mais_pressed();
    void on_um_pressed();
    void on_dois_pressed();
    void on_tres_pressed();
    void on_menos_pressed();
    void on_quatro_pressed();
    void on_cinco_pressed();
    void on_seis_pressed();
    void on_vezes_pressed();
    void on_sete_pressed();
    void on_oito_pressed();
    void on_nove_pressed();
    void on_dividir_pressed();
    void on_limpar_pressed();
    void on_zero_pressed();
    void on_ponto_pressed();
    void on_igual_pressed();
    void on_elevar_pressed();
    void textoCor1();
    void textoCor2();
    void textoCor3();
    void textoCor4();
    void textoCor5();

private:
    Ui::MainWindow *ui;
    void ExibeExpressaoErro();
    void keyPressEvent(QKeyEvent * event);
    void DigitaCaracter(QString Caracter);
    bool ParentesesBalanceados();
    bool NaoHaEspacosVazios();
    string InFixaPadrao(string Texto);
    string ParaString (long double N);
    inline int OndeTermina(int in, string S);
    inline int Prioridade(string A);
    string PosFixa(string Texto);
    string CalculoPosFixa(string Expressao);
    void Calcula();
};

#endif // MAINWINDOW_H
