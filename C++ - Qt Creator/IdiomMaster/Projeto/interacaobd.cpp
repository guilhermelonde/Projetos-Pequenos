#include "interacaobd.h"
#include <iostream>

InteracaoBD* InteracaoBD::instancia = 0;

InteracaoBD::InteracaoBD()
{
    //A = new Arquivo();
    B = new BancoDeDados();
}

list<RegistroBD> InteracaoBD::todos()
{
    //return A->todos();
    return B->todos();
}

void InteracaoBD::limpar()
{
    //A->limpar();
    B->limpar();
}

void InteracaoBD::criar(RegistroBD r)
{
    //A->criar(r);
    B->criar(r);
}

void InteracaoBD::dicionario(string De, string Para)
{
    //A->dicionario(De, Para);
    B->dicionario(De, Para);
}

void InteracaoBD::flush()
{
    //A->flush();
}

InteracaoBD *InteracaoBD::var()
{
    if (instancia == 0){
        instancia = new InteracaoBD();
    }
    return instancia;
}
