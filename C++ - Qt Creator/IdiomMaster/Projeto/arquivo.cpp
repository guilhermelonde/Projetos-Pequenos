#include "arquivo.h"
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <iostream>
#include <QTextStream>

using namespace std;

list<RegistroBD> Arquivo::todos()
{
    list<RegistroBD> saida;
    for (map<pair<string,string>,int> ::iterator x = registros.begin(); x != registros.end(); x++)
    {
        saida.push_back(RegistroBD(x->first.first, x->first.second, x->second));
    }
    return saida;
}

void Arquivo::limpar()
{
    registros.clear();
}

void Arquivo::criar(RegistroBD r)
{
    registros[r.key()] = r.get();
}


void Arquivo::dicionario(string De, string Para)
{
    registros.clear();
    this->De = De;
    this->Para = Para;
    QFile Arq;
    QByteArray QBA;
    string nomeArq = "dic/" + De + "-" + Para;
    Arq.setFileName(QString::fromStdString(nomeArq));
    Arq.open(QIODevice::ReadOnly);
    if (!Arq.isOpen())
        return;
    QBA = Arq.readAll();
    string QBA_Str = QBA.toStdString();
    int i = 0;
    while(QBA_Str.find(";", i) != string::npos)
    {
        int j = QBA_Str.find(",", i);
        string A = QBA_Str.substr(i, j-i);
        int k = QBA_Str.find(",", j+1);
        string B = QBA_Str.substr(j+1, k-(j+1));
        i = QBA_Str.find(";", k+1);
        string C = QBA_Str.substr(k+1, i-(k+1));
        make_pair(make_pair(A, B), (int)(C == "Y" ? 1 : 0));
        registros[make_pair(A, B)] = (C == "Y" ? 1 : 0);
        i++;
    }
}

void Arquivo::flush()
{
    QDir dir;
    if(!dir.exists("dic"))
    {
        dir.mkpath("dic");
    }
    QFile Arq;
    string nomeArq = "dic/" + De + "-" + Para;
    Arq.setFileName(QString::fromStdString(nomeArq));
    Arq.open(QIODevice::WriteOnly);
    QByteArray QBA;
    QTextStream streamArquivo(&Arq);
    streamArquivo.setCodec("Latin1");
    for (map<pair<string,string>,int> ::iterator x = registros.begin(); x != registros.end(); x++)
    {
        string xx = x->first.first + "," + x->first.second + "," + (x->second == 0 ? "N" : "Y") + ";";
        streamArquivo << QString::fromStdString(xx);
    }
    streamArquivo.flush();
    Arq.close();
}
