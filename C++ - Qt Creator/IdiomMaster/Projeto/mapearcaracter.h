#ifndef MAPEARCARACTER_H
#define MAPEARCARACTER_H

#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
class MapearCaracter;
}

class MapearCaracter : public QDialog
{
    Q_OBJECT

public:
    explicit MapearCaracter(QWidget *parent = 0);
    ~MapearCaracter();
    void Parametro(string A, string *B, bool *Mapeou);

private slots:
    void on_ok_pressed();
    void on_cancela_pressed();

private:
    Ui::MapearCaracter *ui;
    string *Str;
    bool *Mp;
};

#endif // MAPEARCARACTER_H
