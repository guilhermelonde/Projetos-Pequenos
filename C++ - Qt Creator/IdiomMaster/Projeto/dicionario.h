#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <vector>
#include <qstring.h>
#include <QFile>
#include "interacaobd.h"
#include "registrobd.h"

using namespace std;

class Dicionario
{
private:
    int Tam, UltimaTrad, traducoes;
    InteracaoBD *BD;
    string Src, For;
    inline bool eTraduzida(string Palavra);

public:
    Dicionario();
    vector <string> Dic;
    vector <int> Praticada;
    void setLinha(string Palavra, bool praticada);
    //bool Importar(string Aux);
    void Exportar();
    //bool AbrirArquivo(QString filename);
    bool AbrirArquivo();
    int getTamanho();
    int procurarPrimeira(QString Palavra, int ind, int ate, int d);
    int procurarSegunda(QString Palavra, int ind, int ate, int d);
    int getUltimaTrad();
    int getTraducoes();
    double getPorcentagem();
    int setPrimeira(QString Palavra);
    void setPrimeira(QString Palavra, int Ind);
    void setSegunda(QString Palavra, int Ind);
    void setSrcFor(string S, string F);
    void limpar();
    string getSrc();
    string getFor();
    void removeLinha(int l);
    string getLinha(int l);
    string getPrimeira(int l);
    string getSegunda(int l);
};

#endif // DICIONARIO_H
