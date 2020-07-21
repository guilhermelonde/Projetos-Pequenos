#ifndef REGISTROBD_H
#define REGISTROBD_H

#include <string>
#include <utility>

using namespace std;

class RegistroBD
{
public:
    string A, B;
    bool praticado;
    RegistroBD(string _A, string _B, bool _praticado) : A(_A), B(_B), praticado(_praticado) {}
    RegistroBD() : praticado(0) {}
    pair<string,string> key() {return pair<string,string> (A, B);}
    void set() {praticado = 1;}
    bool get() {return praticado;}
};

#endif // REGISTROBD_H
