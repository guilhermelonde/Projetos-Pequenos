#include "exibir_progresso.h"
#include "ui_exibir_progresso.h"

Exibir_progresso::Exibir_progresso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exibir_progresso)
{
    ui->setupUi(this);
    setWindowTitle(" ");
    ui->tableWidget->setColumnCount(2);
    QStringList titulos;
    titulos << "Palavra" << "Tradução";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}

Exibir_progresso::~Exibir_progresso()
{
    delete ui;
}

void Exibir_progresso::Exibelista(vector <arquivo> &f)
{
    int n = f.size();
    for (int i = 0; i < n - 1; i++)
    {
        char aux[50];
        char aux_1[70];
        int c;
        for (c = 0; f[i].linha[c] != '\t' && f[i].linha[c] != '\0'; c++)
            aux[c] = f[i].linha[c];
        aux[c] = '\0';
        int rbusk = 0, e = 0;
        for (int d = 0; f[i].linha[d] != '\0'; d++)
        {
            if (f[i].linha[d] == '\t' && !rbusk)
                rbusk = 1;
            if (f[i].linha[d] != '\t' && f[i].linha[d] != '\0' && rbusk)
                rbusk = 2;
            if (rbusk == 2)
            {
                aux_1[e] = f[i].linha[d];
                e++;
            }
        }
        aux_1[e] = '\0';
        QString orig = QString::fromLatin1(aux);
        QString resu = QString::fromLatin1(aux_1);
        ui->tableView->insertRow(ui->tableView->rowCount());
        int fila = ui->tableView->rowCount() - 1;
        ui->tableView->setItem(fila, ORIGEM, new QTableViewItem(orig));
        ui->tableView->setItem(fila, TRADU, new QTableViewItem(resu));
    }
}
