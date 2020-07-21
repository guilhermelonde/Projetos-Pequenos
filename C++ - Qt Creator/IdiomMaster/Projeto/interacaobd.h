#ifndef INTERACAOBD_H
#define INTERACAOBD_H

#include "bancodedados.h"
#include "registrobd.h"
#include "arquivo.h"
#include <list>
#include <string>

using namespace std;

// Implementa Singleton, Adapter e Facade
class InteracaoBD
{
    Arquivo *A;
    BancoDeDados *B;
private:
    InteracaoBD();
    static InteracaoBD *instancia;
public:
    list<RegistroBD> todos();
    void limpar();
    void criar(RegistroBD r);
    void dicionario(string De, string Para);
    void flush();
    InteracaoBD *var();
};

#endif // INTERACAOBD_H
