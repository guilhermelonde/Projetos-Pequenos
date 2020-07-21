#include "dicionario.h"
#include "qfile.h"
#include "qstring.h"
#include "string"
#include "stringfrom.h"
#include <QTextStream>
#include <QSysInfo>
#include <iostream>

using namespace std;

Dicionario::Dicionario()
{
    Tam = 0;
    UltimaTrad = 0;
    traducoes = 0;
}

inline void Dicionario::setLinha(string Palavra, bool praticada = 0)
{
    Tam++;
    Dic.push_back(Palavra);
    Praticada.push_back(praticada);
    if (Dic.size() == UltimaTrad + 1 && getPrimeira(Dic.size() - 1) != "" && getSegunda(Dic.size() - 1) != "")
        UltimaTrad++;
}

inline bool Dicionario::eTraduzida(string Palavra)
{
    if (Palavra.find('\t') != string::npos)
        return 1;
    return 0;
}

void Dicionario::Exportar()
{
    BD->var()->limpar();
    for (int i = 0; i < Tam; i++)
    {
        BD->var()->criar(RegistroBD(StringFrom::ConverteParaAscii(Src, getPrimeira(i)).toStdString(), StringFrom::ConverteParaAscii(For, getSegunda(i)).toStdString(), Praticada[i]));
    }
    BD->var()->flush();
}

bool Dicionario::AbrirArquivo()
{
    Dic.erase(Dic.begin(), Dic.end());
    Tam = 0;
    UltimaTrad = 0;
    traducoes = 0;
    bool JaTemUltimaTrad = 0;
    list<RegistroBD> L = BD->var()->todos();
    while(!L.empty()){
        pair<string, string> p = L.front().key();
        if (p.second != ""){
            if (Tam == 0)
            {
                JaTemUltimaTrad = 1;
                UltimaTrad = 1;
            }
            traducoes++;
        }
        if (JaTemUltimaTrad && Tam != 0)
        {
            if (p.second != "")
                UltimaTrad++;
            else
                JaTemUltimaTrad = 0;
        }
        string aux;
        StringFrom::Converte(Src, For, p.first + "\t" + p.second, aux);
        setLinha(aux.substr(0, aux.size()-1), L.front().get());
        L.pop_front();
    }
    return 1;
}

int Dicionario::getTamanho()
{
    return Tam;
}

int Dicionario::procurarPrimeira(QString Palavra, int ind, int ate, int d)
{
    if (ind < 0 || ind >= ate)
        ind = 0;
    for (int i = ind + d; i >= 0 && i < ate; i+=d)
    {
        string ss = getPrimeira(i);
        if (ss.find(Palavra.toStdString()) != string::npos)
            return i;
    }
    return -1;
}

int Dicionario::procurarSegunda(QString Palavra, int ind, int ate, int d)
{
    if (ind < 0 || ind >= ate)
        ind = 0;
    for (int i = ind + d; i >= 0 && i < ate; i+=d)
    {
        string ss = getSegunda(i);
        if (ss.find(Palavra.toStdString()) != string::npos)
            return i;
    }
    return -1;
}

int Dicionario::getUltimaTrad()
{
    return UltimaTrad;
}

int Dicionario::getTraducoes()
{
    return traducoes;
}

double Dicionario::getPorcentagem()
{
    if (!Tam)
        return 100;
    double tamDouble = Tam;
    return (traducoes/tamDouble)*100;
}

int Dicionario::setPrimeira(QString Palavra)
{
    char lf = 10;
    string P = Palavra.toStdString();
    Dic.push_back(P);
    Praticada.push_back(0);
    int i = Tam;
    Tam++;
    while (i > 0 && StringFrom::ComparaStrings(getPrimeira(i), getPrimeira(i - 1), Src) < 0)
    {
        string troca = Dic[i];
        bool p = Praticada[i];
        Dic[i] = Dic[i - 1];
        Praticada[i] = Praticada[i - 1];
        Dic[i - 1] = troca;
        Praticada[i - 1] = p;
        i--;
    }
    if (i < UltimaTrad)
        UltimaTrad++;
    return i;
}

void Dicionario::setPrimeira(QString Palavra, int Ind)
{
    char lf = 10;
    string P = Palavra.toStdString();
    Dic.push_back(P);
    Praticada.push_back(0);
    int i = Tam;
    Tam++;
    while (i > Ind)
    {
        string troca = Dic[i];
        bool p = Praticada[i];
        Dic[i] = Dic[i - 1];
        Praticada[i] = Praticada[i - 1];
        Dic[i - 1] = troca;
        Praticada[i - 1] = p;
        i--;
    }
    if (i < UltimaTrad)
        UltimaTrad++;
}

void Dicionario::setSegunda(QString Palavra, int Ind)
{
    if (Ind < 0 || Ind >= Dic.size())
        return;
    if (getSegunda(Ind) == "")
    {
        if (UltimaTrad == Ind)
            UltimaTrad++;
        int i = Ind + 1;
        while (i == UltimaTrad && UltimaTrad < Tam && getSegunda(i++) != "")
            UltimaTrad++;
        traducoes++;
    }
    Dic[Ind] = getPrimeira(Ind) + "\t" + Palavra.toStdString();
    Praticada[Ind] = 0;
}

void Dicionario::setSrcFor(string S, string F)
{
    Src = S;
    For = F;
    BD->var()->dicionario(S, F);
    AbrirArquivo();
}

void Dicionario::limpar()
{
    Dic.clear();
    Praticada.clear();
    Tam = 0;
    UltimaTrad = 0;
}

string Dicionario::getSrc()
{
    return Src;
}

string Dicionario::getFor()
{
    return For;
}

void Dicionario::removeLinha(int l)
{
    if (getSegunda(l) != "")
    {
        traducoes--;
        if (l <= UltimaTrad)
            UltimaTrad--;
    }
    Dic.erase(Dic.begin() + l);
    Praticada.erase(Praticada.begin() + l);
    Tam--;
}

string Dicionario::getLinha(int l)
{
    if (l >= 0 && l < Dic.size())
        return Dic[l];
}

string Dicionario::getPrimeira(int l)
{
    string Devolv = Dic[l];
    int fn;
    if (eTraduzida(Devolv))
        fn = Devolv.find('\t');
    else
        fn = Devolv.size();
    return Devolv.substr(0, fn);
}

string Dicionario::getSegunda(int l)
{
    string Devolv = Dic[l];
    int fn = -1, fn2;
    if (!eTraduzida(Devolv))
    {
        string Q;
        return Q;
    }
    do
    {
        fn = Devolv.find('\t', fn+1);
        fn2 = Devolv.find('\t', fn+1);
    }while (fn2 != string::npos);
    return Devolv.substr(fn+1, Devolv.size() - 1);
}
