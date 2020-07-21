#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include <list>
#include <map>
#include <utility>
#include "registrobd.h"

using namespace std;

class Arquivo
{
private:
    string De, Para;
    map<pair<string,string>,int > registros;
public:
    list<RegistroBD> todos();
    void limpar();
    void criar(RegistroBD r);
    void dicionario(string De, string Para);
    void flush();
};

#endif // ARQUIVO_H
