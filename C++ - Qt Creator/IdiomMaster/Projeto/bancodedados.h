#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

#include <QtSql/QSqlDatabase>
#include <list>
#include <QString>
#include "registrobd.h"

class BancoDeDados
{
    QString dic;
    QSqlDatabase db;
public:
    list<RegistroBD> todos();
    void limpar();
    void criar(RegistroBD r);
    void dicionario(string De, string Para);
    BancoDeDados();
    ~BancoDeDados();
};

#endif // BANCODEDADOS_H
