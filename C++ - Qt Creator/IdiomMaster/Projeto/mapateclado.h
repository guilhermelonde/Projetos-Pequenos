#ifndef MAPATECLADO_H
#define MAPATECLADO_H

#include <QDialog>
#include <string>
#include <vector>
using namespace std;

namespace Ui {
class MapaTeclado;
}

class MapaTeclado : public QDialog
{
    Q_OBJECT

public:
    explicit MapaTeclado(QWidget *parent = 0);
    ~MapaTeclado();
    void Inicializa(string Para);
    bool listaDeOpcoes(string k, int x, int y);
    string getElemento();

private slots:
    void on_pushButton_pressed();
    void on_tabela_cellActivated(int row, int column);

private:
    Ui::MapaTeclado *ui;
    string elemento;
    vector <int> Mapa;
    bool PodeEditar;
    enum coluna {ORIGEM, CHAVE};
    void SetNew(string Idioma);
};

#endif // MAPATECLADO_H
