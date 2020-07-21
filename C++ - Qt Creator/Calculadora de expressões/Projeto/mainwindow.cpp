#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <iostream>
#include <QTimer>
#include <stack>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textoCor5();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ExibeExpressaoErro()
{
    //A cada 70 milisegundos, alterará a StyleSheet do LineEdit texto, de modo que simule uma rápida animação que durará 350 milisegundos
    QTimer::singleShot(70, this, SLOT(textoCor1()));
    QTimer::singleShot(140, this, SLOT(textoCor2()));
    QTimer::singleShot(210, this, SLOT(textoCor3()));
    QTimer::singleShot(280, this, SLOT(textoCor4()));
    QTimer::singleShot(350, this, SLOT(textoCor5()));
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (event->text() == "+")
        ui->mais->pressed();
    if (event->text() == "-")
        ui->menos->pressed();
    if (event->text() == "*")
        ui->vezes->pressed();
    if (event->text() == "/")
        ui->dividir->pressed();
    if (event->text() == "^")
        ui->elevar->pressed();
    if (event->text() == "(")
        ui->abreParanteses->pressed();
    if (event->text() == ")")
        ui->fechaParenteses->pressed();
    if (event->text() == "")
        ui->backspace->pressed();
    if (event->text() == "=" || event->text() == "\r")
        ui->igual->pressed();
    if (event->text() == "")
        ui->limpar->pressed();
    if (event->text() == "1")
        ui->um->pressed();
    if (event->text() == "2")
        ui->dois->pressed();
    if (event->text() == "3")
        ui->tres->pressed();
    if (event->text() == "4")
        ui->quatro->pressed();
    if (event->text() == "5")
        ui->cinco->pressed();
    if (event->text() == "6")
        ui->seis->pressed();
    if (event->text() == "7")
        ui->sete->pressed();
    if (event->text() == "8")
        ui->oito->pressed();
    if (event->text() == "9")
        ui->nove->pressed();
    if (event->text() == "0")
        ui->zero->pressed();
    if (event->text() == ".")
        ui->ponto->pressed();
}

void MainWindow::DigitaCaracter(QString Caracter)
{
    ui->texto->setText(ui->texto->text() + Caracter);
}

bool MainWindow::ParentesesBalanceados()
{
    stack <QChar> P;
    int tam = ui->texto->text().size(), i;
    for (i = 0; i < tam; i++)
        if (ui->texto->text()[i] == '(' || ui->texto->text()[i] == ')')
        {
            if (ui->texto->text()[i] == '(')
                P.push(ui->texto->text()[i]);
            else if (P.empty() || (ui->texto->text()[i] == ')' && P.top() != '('))
                    return 0;
                else
                    P.pop();
        }
    return P.empty();
}

bool MainWindow::NaoHaEspacosVazios()
{
    string F = ui->texto->text().toStdString();
    if (F[0] == '*' || F[0] == '^' || F[0] == '/' || F[0] == '+')
        return 0;
    for (int i = 0; i < (int)F.size(); i++)
        if (F[i] == '*' || F[i] == '^' || F[i] == '/' || F[i] == '+' || F[i] == '-' || F[i] == '(')
            if (i + 1 == (int)F.size() || F[i+1] == '*' || F[i+1] == '^' || F[i+1] == '/' || F[i+1] == '+' || F[i+1] == ')')
                return 0;
    return 1;
}

string MainWindow::InFixaPadrao(string Texto)
{
    //Expressões como (3+4)(5*6) ou 7(5+8) ou (7-2)6 passarão a ser (3+4)*(5*6) e 7*(5+8) e (7-2)*6
    for (int i = 0; i < (int)Texto.size() - 1; i++)
    {
        int u = OndeTermina(i, Texto);
        if (((Texto[i] == ')' || ((Texto[i] >= '0' && Texto[i] <= '9') || Texto[i] == '.')) && Texto[u] == '(')||(Texto[i] == ')' && ((Texto[i+1] >= '0' && Texto[i+1] <= '9') || Texto[i+1] == '.')))
            Texto = Texto.substr(0, u) + "*" + Texto.substr(u, Texto.size());
    }
    //Expressões como (6) passarão a ser 6
    for (int i = 0; i < (int)Texto.size() - 1; i++)
    {
        int u = OndeTermina(i+1, Texto);
        if (Texto[i] == '(' && Texto[u] == ')')
            Texto = Texto.substr(0, i) + Texto.substr(i+1, u - i - 1) + Texto.substr(u+1, string::npos);
    }
    //Expressões como -1+2 ou 2+-1 ou 3*-1 ou 2*(-1) passarão a ser (0-1)+2 e 2+(0-1) e 3*(0-1) e 2*(0-1)
    for (int i = 0; i < (int)Texto.size() - 1; i++)
        if (Texto[i] == '-' && (i == 0 || Texto[i-1] == '(' || Texto[i-1] == '+' || Texto[i-1] == '*' || Texto[i-1] == '^' || Texto[i-1] == '/' || Texto[i-1] == '-'))
        {
            int k = OndeTermina(i+1, Texto);
            if (Texto[i-1] != '(')
                Texto = Texto.substr(0, i) + "(0" + Texto.substr(i, k - i) + ")" + Texto.substr(k, Texto.size());
            else
                Texto = Texto.substr(0, i) + "0" + Texto.substr(i, k - i) + Texto.substr(k, Texto.size());
            i++;
        }
    return Texto;
}

string MainWindow::ParaString (long double N)
{
    //Evita aparecer a notação científica na saída
    long long PtInteira = N;
    double ND;
    string Saida = QString::number(PtInteira).toStdString(), Decimal;;
    if ((double)PtInteira != N)
    {
        if ((double)PtInteira > N)
            ND = (double)PtInteira - N;
        else
            ND = N - (double)PtInteira;
        //mostrará até a 7a casa após a vírgula
        ND = 100000000 + (int)(ND*10000000.0);
        Decimal = QString::number((int)ND).toStdString();
        Decimal.erase(0, 2);
        while (Decimal[Decimal.size() - 1] == '0')
            Decimal.erase(Decimal.size() - 1, 1);
        if (Decimal != "")
            Saida = Saida + "." + Decimal;
    }
    return Saida;
}

int MainWindow::OndeTermina(int in, string S)
{
    if (S[in] == '(' || S[in] == ')' || S[in] == '*' || S[in] == '-' || S[in] == '+' || S[in] == '/' || S[in] == '^')
        in++;
    else
        while (in < (int)S.size() && ((S[in] >= '0' && S[in] <= '9') || S[in] == '.'))
            in++;
    return in;
}

int MainWindow::Prioridade(string A)
{
    if (A == "(")
        return 4;
    if (A == "^")
        return 3;
    if (A == "*" || A == "/")
        return 2;
    if (A == "+" || A == "-")
        return 1;
    return 0;
}

string MainWindow::PosFixa(string Texto)
{
    stack <string> op;
    string Saida, z;
    for (int i = 0; i < (int)Texto.size(); i = OndeTermina(i, Texto))
    {
        string Var = Texto.substr(i, OndeTermina(i, Texto) - i);
        if ((Var[0] >= '0' && Var[0] <= '9') || (Var[0] == '.'))
            Saida = Saida + Var + " ";
        else if (op.empty() || (!op.empty() && op.top() == "("))
                op.push(Var);
            else if (Prioridade(Var) > Prioridade(op.top()))
                    op.push(Var);
                else
                {
                    do
                    {
                        z = op.top();
                        op.pop();
                        if (z != "(")
                            Saida = Saida + z + " ";
                    }while (!op.empty() && z != "(" && Prioridade(z) > Prioridade(Var));
                    if (Var != ")")
                        op.push(Var);
                }
    }
    while (!op.empty())
    {
        if (op.top() != "(")
            Saida = Saida + op.top() + " ";
        op.pop();
    }
    return Saida;
}

string MainWindow::CalculoPosFixa(string Expressao)
{
    stack <long double> P;
    for (int i = 0; i < (int)Expressao.size() - 1;)
    {
        int k = OndeTermina(i, Expressao);
        string Var = Expressao.substr(i, k - i);
        i = k + 1;
        if ((Var[0] >= '0' && Var[0] <= '9') || Var[0] == '.')
            P.push(QString::fromStdString(Var).toDouble());
        else
        {
            long double Top = P.top();
            P.pop();
            if (P.empty())
            {
                ExibeExpressaoErro();
                return ui->texto->text().toStdString();
            }
            if (Var == "+")
                P.top() += Top;
            if (Var == "-")
                P.top() -= Top;
            if (Var == "*")
                P.top() *= Top;
            if (Var == "/")
                P.top() /= Top;
            if (Var == "^")
                P.top() = pow(P.top(), Top);
        }
    }
    return ParaString(P.top());
}

void MainWindow::Calcula()
{
    QString temp = ui->texto->text();
    if (temp == "")
        return;

    if (!ParentesesBalanceados() || !NaoHaEspacosVazios())
    {
        ExibeExpressaoErro();
        ui->texto->setText(temp);
        return;
    }
    cout << "------Novo Calculo------\n";
    string Texto = ui->texto->text().toStdString();
    cout << "Expressao original: " << Texto << endl;
    Texto = InFixaPadrao(Texto);
    cout << "In Fixa Padrao: " << Texto << endl;
    Texto = PosFixa(Texto);
    cout << "Pos fixa: " << Texto << endl;
    string Result = CalculoPosFixa(Texto);
    cout << "Resultado: " << Result << endl;
    ui->texto->setText(QString::fromStdString(Result));
}

void MainWindow::on_backspace_pressed()
{
    QString N = ui->texto->text();
    N.remove(N.size() - 1, 1);
    ui->texto->setText(N);
}

void MainWindow::on_abreParanteses_pressed()
{
    DigitaCaracter("(");
}

void MainWindow::on_fechaParenteses_pressed()
{
    DigitaCaracter(")");
}

void MainWindow::on_mais_pressed()
{
    DigitaCaracter("+");
}

void MainWindow::on_um_pressed()
{
    DigitaCaracter("1");
}

void MainWindow::on_dois_pressed()
{
    DigitaCaracter("2");
}

void MainWindow::on_tres_pressed()
{
    DigitaCaracter("3");
}

void MainWindow::on_menos_pressed()
{
    DigitaCaracter("-");
}

void MainWindow::on_quatro_pressed()
{
    DigitaCaracter("4");
}

void MainWindow::on_cinco_pressed()
{
    DigitaCaracter("5");
}

void MainWindow::on_seis_pressed()
{
    DigitaCaracter("6");
}

void MainWindow::on_vezes_pressed()
{
    DigitaCaracter("*");
}

void MainWindow::on_sete_pressed()
{
    DigitaCaracter("7");
}

void MainWindow::on_oito_pressed()
{
    DigitaCaracter("8");
}

void MainWindow::on_nove_pressed()
{
    DigitaCaracter("9");
}

void MainWindow::on_dividir_pressed()
{
    DigitaCaracter("/");
}

void MainWindow::on_limpar_pressed()
{
    ui->texto->setText("");
}

void MainWindow::on_zero_pressed()
{
    DigitaCaracter("0");
}

void MainWindow::on_ponto_pressed()
{
    DigitaCaracter(".");
}

void MainWindow::on_igual_pressed()
{
    if (ui->texto->text() != "ERRO")
        Calcula();
}

void MainWindow::on_elevar_pressed()
{
    DigitaCaracter("^");
}

void MainWindow::textoCor1()
{
    ui->texto->setStyleSheet("background-color: rgb(255, 50, 50);""color: black;""border-style: outset;""border-width: 2px;""border-color: rgb(70, 70, 70);");
}

void MainWindow::textoCor2()
{
    ui->texto->setStyleSheet("background-color: rgb(240, 90, 90);""color: black;""border-style: outset;""border-width: 2px;""border-color: rgb(70, 70, 70);");
}

void MainWindow::textoCor3()
{
    ui->texto->setStyleSheet("background-color: rgb(225, 130, 130);""color: black;""border-style: outset;""border-width: 2px;""border-color: rgb(70, 70, 70);");
}

void MainWindow::textoCor4()
{
    ui->texto->setStyleSheet("background-color: rgb(210, 170, 170);""color: black;""border-style: outset;""border-width: 2px;""border-color: rgb(70, 70, 70);");
}

void MainWindow::textoCor5()
{
    ui->texto->setStyleSheet("background-color: rgb(200, 200, 200);""color: black;""border-style: outset;""border-width: 2px;""border-color: rgb(70, 70, 70);");
}
