#ifndef PRATICAR_H
#define PRATICAR_H

#include <QDialog>

namespace Ui {
class Praticar;
}

class Praticar : public QDialog
{
    Q_OBJECT

public:
    explicit Praticar(QWidget *parent = 0);
    ~Praticar();

private:
    Ui::Praticar *ui;
};

#endif // PRATICAR_H
