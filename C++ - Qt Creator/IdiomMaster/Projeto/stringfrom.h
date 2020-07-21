#ifndef STRINGFROM_H
#define STRINGFROM_H
#include <string>
#include <QString>
#include <vector>

using namespace std;


class StringFrom
{
private:
    static inline void ConvertePara(string Para, string S, string &A);
    static inline bool Separa(string &A, string &B, string &Orig);
    static inline string AlteraCaracteresPor(string A, string Chars, string CharsPara);
    static inline int ContaCaracteres(string A, string Chars);
    static inline void remove(string &S, int i, int j);
public:
    static bool IdiomaValido(string Ling);
    static void Converte(string Prim, string Seg, string S, string &A);
    static QString ConverteParaAscii(string Ling, string S);
    static string StringComparavel(string A, string Ling);
    static int ComparaStrings(string A, string B, string Ling);
    static int QuantidadeCaracteres(string A, string Ling);
    static bool EProibido(string A, string Ling);
    static bool NaoPodeEstarNaFrente(string A);
    static bool NaoPodeEstarAtras(string A);
    static bool ESubstring(string A, string &B, bool Remover, string Ling);
    static bool PalavrasSubstring(string &A, string &B, string Ling, bool Remover, int &Contagem);
    static void InverteOrdemVetor(vector <string> &A, vector <string> B, string Ling);
};

#endif // STRINGFROM_H
