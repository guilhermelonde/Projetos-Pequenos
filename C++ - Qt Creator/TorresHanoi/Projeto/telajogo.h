#ifndef TELAJOGO_H
#define TELAJOGO_H

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>
#include <stack>
#include <QPushButton>
#include <QLabel>
#include <QString>
#define MAX_Discos 7

using namespace std;

namespace Ui {
class TelaJogo;
}

class TelaJogo : public QWidget
{
    Q_OBJECT

public:
    explicit TelaJogo(QWidget *parent = 0);
    ~TelaJogo();
    void setaDiscos(int q);
    void botoesFazerDesfazer(QPushButton * B1, QPushButton * B2);
    void labelMovimentos(QLabel * L);
    void desfazer();
    void refazer();

private:
    Ui::TelaJogo *ui;
    QFrame *Frames[MAX_Discos];
    int QtDiscos;
    int Movimentos;
    int pinoDestacado;
    bool Disponivel;
    bool Contavel;
    QString DesignDiscoAmarelo, DesignDiscoAzul;
    stack <QFrame *> *pino[3];
    QPushButton * BotaoDesfazer;
    QPushButton * BotaoRefazer;
    QLabel * LabelMovimentos;
    stack <int *> consoleDesfazer;
    stack <int *> consoleRefazer;
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    int DestacaPino(int x, int y);
    bool moveDisco(int pinoA, int pinoB, int DesfazerModo);
    void setaDisco(int pino, QFrame * disco);
};

#endif // TELAJOGO_H
