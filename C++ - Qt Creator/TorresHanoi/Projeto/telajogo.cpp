#include "telajogo.h"
#include "ui_telajogo.h"
#include <QMessageBox>
#include <iostream>

TelaJogo::TelaJogo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TelaJogo)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");

    pinoDestacado = 0;
    Disponivel = 0;
    Contavel = 1;
    DesignDiscoAmarelo = "background-color: yellow;border-color: black;border-width: 2 px;border-right: 2 px;border-left: 2 px;border-style: outset;";
    DesignDiscoAzul = "background-color: blue;border-color: black;border-width: 2 px;border-right: 2 px;border-left: 2 px;border-style: outset;";

    pino[0] = new stack <QFrame *>;
    pino[1] = new stack <QFrame *>;
    pino[2] = new stack <QFrame *>;

    int t = 28;
    for (int i = 0; i < MAX_Discos; i++)
    {
        Frames[i] = new QFrame (this);
        Frames[i]->setGeometry(0, 0, t, 20);
        Frames[i]->hide();
        t += 10;
    }
}

TelaJogo::~TelaJogo()
{
    delete ui;
}

void TelaJogo::setaDiscos(int q)
{
    Movimentos = 0;
    LabelMovimentos->setText("Movimentos: 0");
    Disponivel = 1;
    QtDiscos = q;
    for (int i = 0; i < MAX_Discos; i++)
        Frames[i]->hide();
    int h = ui->pino1->y() + ui->pino1->height();
    int x = ui->pino1->x() + 4;
    for (int i = 0; i < 3; i++)
        while (!pino[i]->empty())
            pino[i]->pop();
    for (int i = q - 1; i >= 0; i--)
    {
        h -= 20;
        Frames[i]->setGeometry(x - Frames[i]->width()/2, h, Frames[i]->width(), 20);
        Frames[i]->show();
        Frames[i]->setStyleSheet(DesignDiscoAmarelo);
        pino[0]->push(Frames[i]);
    }
}

void TelaJogo::botoesFazerDesfazer(QPushButton * B1, QPushButton * B2)
{
    BotaoDesfazer = B1;
    BotaoRefazer = B2;
    B1->setEnabled(false);
    B2->setEnabled(false);
    while (!consoleDesfazer.empty())
        consoleDesfazer.pop();
    while (!consoleRefazer.empty())
        consoleRefazer.pop();
}

void TelaJogo::labelMovimentos(QLabel * L)
{
    LabelMovimentos = L;
}

void TelaJogo::mousePressEvent(QMouseEvent * event)
{
    if (!Disponivel)
        return;
    if (event->buttons() & Qt::RightButton || event->buttons() & Qt::MidButton)
    {
        mouseReleaseEvent(event);
        return;
    }
    pinoDestacado = DestacaPino(event->x(), event->y());
    if (pinoDestacado && !pino[pinoDestacado-1]->empty())
        pino[pinoDestacado-1]->top()->setStyleSheet(DesignDiscoAzul);
}

void TelaJogo::mouseMoveEvent(QMouseEvent * event)
{
    if (!Disponivel || pinoDestacado == 0 || pino[pinoDestacado-1]->empty() || event->buttons() & Qt::RightButton || event->buttons() & Qt::MidButton || (event->x() <= 0 || event->y() <= 0 || (event->x() >= this->width()) || (event->y() >= this->height())))
    {
        mouseReleaseEvent(event);
        return;
    }
    pino[pinoDestacado-1]->top()->setGeometry(event->x() - (pino[pinoDestacado-1]->top()->width()/2), event->y()-10, pino[pinoDestacado-1]->top()->width(), pino[pinoDestacado-1]->top()->height());
}

void TelaJogo::mouseReleaseEvent(QMouseEvent * event)
{
    if (!Disponivel)
        return;
    if (pinoDestacado && !pino[pinoDestacado-1]->empty())
    {
        pino[pinoDestacado-1]->top()->setStyleSheet(DesignDiscoAmarelo);
        if (!moveDisco(pinoDestacado, DestacaPino(event->x(), event->y()), 1))
        {
            Contavel = 0;
            QFrame *u = pino[pinoDestacado-1]->top();
            pino[pinoDestacado-1]->pop();
            setaDisco(pinoDestacado, u);
            Contavel = 1;
        }
    }
    pinoDestacado = 0;
}

int TelaJogo::DestacaPino(int x, int y)
{
    if (y < 30 || y > 220)
        return 0;
    if (x >= 30 && x <= 120)
        return 1;
    if (x >= 150 && x <= 250)
        return 2;
    if (x >= 280 && x <= 370)
        return 3;
    return 0;
}

bool TelaJogo::moveDisco(int pinoA, int pinoB, int DesfazerModo)
{
    if (!pinoB || (pinoA == pinoB) || (pino[pinoB-1]->size() != 0 && (pino[pinoA-1]->top()->width() > pino[pinoB-1]->top()->width())))
        return 0;
    QFrame * disco = pino[pinoA-1]->top();
    pino[pinoA-1]->pop();
    setaDisco(pinoB, disco);
    int *CD = new int [2];
    CD[0] = pinoB;
    CD[1] = pinoA;
    if (DesfazerModo == 1)
    {
        consoleDesfazer.push(CD);
        BotaoDesfazer->setEnabled(true);
        while (!consoleRefazer.empty())
            consoleRefazer.pop();
        BotaoRefazer->setEnabled(false);
    }
    if (DesfazerModo == 2)
    {
        consoleDesfazer.push(CD);
        BotaoDesfazer->setEnabled(true);
    }
    if (DesfazerModo == 3)
    {
        consoleRefazer.push(CD);
        BotaoRefazer->setEnabled(true);
    }
    if ((int)pino[2]->size() == QtDiscos)
    {
        QMessageBox::information(0," ","Parabéns! Desafio concluído");
        Disponivel = 0;
        BotaoDesfazer->setEnabled(false);
        BotaoRefazer->setEnabled(false);
    }
    return 1;
}

void TelaJogo::setaDisco(int pino, QFrame * disco)
{
    if (Contavel)
        Movimentos++;
    LabelMovimentos->setText("Movimentos: " + QString::number(Movimentos));
    int h = ui->pino1->y() + ui->pino1->height() - (this->pino[pino-1]->size() * 20) - 20, x = (disco->width() / 2);
    if (pino == 1)
        x = ui->pino1->x() - x + 4;
    if (pino == 2)
        x = ui->pino2->x() - x + 4;
    if (pino == 3)
        x = ui->pino3->x() - x + 4;
    disco->setGeometry(x, h, disco->width(), 20);
    this->pino[pino-1]->push(disco);
}

void TelaJogo::desfazer()
{
    int *p = consoleDesfazer.top();
    consoleDesfazer.pop();
    if (consoleDesfazer.empty())
        BotaoDesfazer->setEnabled(false);
    moveDisco(p[0], p[1], 3);
}

void TelaJogo::refazer()
{
    int *p = consoleRefazer.top();
    consoleRefazer.pop();
    if (consoleRefazer.empty())
        BotaoRefazer->setEnabled(false);
    moveDisco(p[0], p[1], 2);
}
