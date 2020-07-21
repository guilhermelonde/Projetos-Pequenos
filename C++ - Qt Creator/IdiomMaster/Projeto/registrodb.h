#ifndef REGISTRODB_H
#define REGISTRODB_H

#include <string>
using namespace std;

class RegistroDB
{
public:
    string A; // chave primária
    string B;
    int praticado;

    RegistroDB(string _A, string _B, int _praticado)
    {
        A = _A;
        B = _B;
        praticado = _praticado;
    }
};

#endif // REGISTRODB_H
