#ifndef NOVAPALAVRA_H
#define NOVAPALAVRA_H

#include <QDialog>

namespace Ui {
class NovaPalavra;
}

class NovaPalavra : public QDialog
{
    Q_OBJECT

public:
    explicit NovaPalavra(QWidget *parent = 0);
    ~NovaPalavra();
    void Parametro(QString *Nova);

private slots:
    void on_linha_editingFinished();
    void on_ok_pressed();

private:
    Ui::NovaPalavra *ui;
    QString *Nova;
};

#endif // NOVAPALAVRA_H
