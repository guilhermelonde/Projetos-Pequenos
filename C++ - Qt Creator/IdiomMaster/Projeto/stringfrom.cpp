#include "stringfrom.h"
#include "string"
#include <iostream>

inline void StringFrom::ConvertePara(string Para, string S, string &A)
{
    if (Para == "EN")
    {
        for (int i = 0; i < S.size(); i++)
            if (S[i] == 9 || S[i] == 10 || S[i] == 13 || S[i] == 32 || S[i] == 33 || (S[i] >= 39 && S[i] <= 59) || (S[i] >= 63 && S[i] <= 90) || (S[i] >= 97 && S[i] <= 122))
                A += S[i];
        return;
    }
    if (Para == "GE")
    {
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == 9 || S[i] == 10 || S[i] == 13 || S[i] == 32 || S[i] == 33 || (S[i] >= 39 && S[i] <= 59) || (S[i] >= 63 && S[i] <= 90) || (S[i] >= 97 && S[i] <= 122))
                A += S[i];
            if (S[i] == -60)
                A += "Ä";
            if (S[i] == -42)
                A += "Ö";
            if (S[i] == -36)
                A += "Ü";
            if (S[i] == -31)
                A += "ß";
            if (S[i] == -28)
                A += "ä";
            if (S[i] == -10)
                A += "ö";
            if (S[i] == -4)
                A += "ü";
        }
        return;
    }

    if (Para == "IT")
    {
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == 9 || S[i] == 10 || S[i] == 13 || S[i] == 32 || S[i] == 33 || (S[i] >= 39 && S[i] <= 59) || (S[i] >= 63 && S[i] <= 90) || (S[i] >= 97 && S[i] <= 122))
                A += S[i];
            if (S[i] == -64)
                A += "À";
            if (S[i] == -56)
                A += "È";
            if (S[i] == -55)
                A += "É";
            if (S[i] == -52)
                A += "Ì";
            if (S[i] == -46)
                A += "Ò";
            if (S[i] == -39)
                A += "Ù";
            if (S[i] == -32)
                A += "à";
            if (S[i] == -24)
                A += "è";
            if (S[i] == -23)
                A += "é";
            if (S[i] == -20)
                A += "ì";
            if (S[i] == -14)
                A += "ò";
            if (S[i] == -7)
                A += "ù";
            if (S[i] == -4)
                A += "ü";
        }
        return;
    }
    if (Para == "PT")
    {
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == 9 || S[i] == 10 || S[i] == 13 || S[i] == 32 || S[i] == 33 || (S[i] >= 39 && S[i] <= 59) || (S[i] >= 63 && S[i] <= 90) || (S[i] >= 97 && S[i] <= 122))
                A += S[i];
            if (S[i] == -64)
                A += "À";
            if (S[i] == -63)
                A += "Á";
            if (S[i] == -62)
                A += "Â";
            if (S[i] == -61)
                A += "Ã";
            if (S[i] == -57)
                A += "Ç";
            if (S[i] == -55)
                A += "É";
            if (S[i] == -54)
                A += "Ê";
            if (S[i] == -51)
                A += "Í";
            if (S[i] == -45)
                A += "Ó";
            if (S[i] == -44)
                A += "Ô";
            if (S[i] == -43)
                A += "Õ";
            if (S[i] == -38)
                A += "Ú";
            if (S[i] == -32)
                A += "à";
            if (S[i] == -31)
                A += "á";
            if (S[i] == -30)
                A += "â";
            if (S[i] == -29)
                A += "ã";
            if (S[i] == -25)
                A += "ç";
            if (S[i] == -23)
                A += "é";
            if (S[i] == -22)
                A += "ê";
            if (S[i] == -19)
                A += "í";
            if (S[i] == -13)
                A += "ó";
            if (S[i] == -12)
                A += "ô";
            if (S[i] == -11)
                A += "õ";
            if (S[i] == -6)
                A += "ú";
        }
        return;
    }
    if (Para == "RU")
    {
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == 9 || S[i] == 10 || S[i] == 13 || S[i] == 32 || S[i] == 33 || (S[i] >= 39 && S[i] <= 59) || S[i] == 63)
                A += S[i];
            if (S[i] == -68)
                A += "Ё";
            if (S[i] == -67)
                A += "ё";
            if (S[i] == -64)
                A += "А";
            if (S[i] == -63)
                A += "Б";
            if (S[i] == -62)
                A += "В";
            if (S[i] == -61)
                A += "Г";
            if (S[i] == -60)
                A += "Д";
            if (S[i] == -59)
                A += "Е";
            if (S[i] == -58)
                A += "Ж";
            if (S[i] == -57)
                A += "З";
            if (S[i] == -56)
                A += "И";
            if (S[i] == -55)
                A += "Й";
            if (S[i] == -54)
                A += "К";
            if (S[i] == -53)
                A += "Л";
            if (S[i] == -52)
                A += "М";
            if (S[i] == -51)
                A += "Н";
            if (S[i] == -50)
                A += "О";
            if (S[i] == -49)
                A += "П";
            if (S[i] == -48)
                A += "Р";
            if (S[i] == -47)
                A += "С";
            if (S[i] == -46)
                A += "Т";
            if (S[i] == -45)
                A += "У";
            if (S[i] == -44)
                A += "Ф";
            if (S[i] == -43)
                A += "Х";
            if (S[i] == -42)
                A += "Ц";
            if (S[i] == -41)
                A += "Ч";
            if (S[i] == -40)
                A += "Ш";
            if (S[i] == -39)
                A += "Щ";
            if (S[i] == -38)
                A += "Ъ";
            if (S[i] == -37)
                A += "Ы";
            if (S[i] == -36)
                A += "Ь";
            if (S[i] == -35)
                A += "Э";
            if (S[i] == -34)
                A += "Ю";
            if (S[i] == -33)
                A += "Я";
            if (S[i] == -32)
                A += "а";
            if (S[i] == -31)
                A += "б";
            if (S[i] == -30)
                A += "в";
            if (S[i] == -29)
                A += "г";
            if (S[i] == -28)
                A += "д";
            if (S[i] == -27)
                A += "е";
            if (S[i] == -26)
                A += "ж";
            if (S[i] == -25)
                A += "з";
            if (S[i] == -24)
                A += "и";
            if (S[i] == -23)
                A += "й";
            if (S[i] == -22)
                A += "к";
            if (S[i] == -21)
                A += "л";
            if (S[i] == -20)
                A += "м";
            if (S[i] == -19)
                A += "н";
            if (S[i] == -18)
                A += "о";
            if (S[i] == -17)
                A += "п";
            if (S[i] == -16)
                A += "р";
            if (S[i] == -15)
                A += "с";
            if (S[i] == -14)
                A += "т";
            if (S[i] == -13)
                A += "у";
            if (S[i] == -12)
                A += "ф";
            if (S[i] == -11)
                A += "х";
            if (S[i] == -10)
                A += "ц";
            if (S[i] == -9)
                A += "ч";
            if (S[i] == -8)
                A += "ш";
            if (S[i] == -7)
                A += "щ";
            if (S[i] == -6)
                A += "ъ";
            if (S[i] == -5)
                A += "ы";
            if (S[i] == -4)
                A += "ь";
            if (S[i] == -3)
                A += "э";
            if (S[i] == -2)
                A += "ю";
            if (S[i] == -1)
                A += "я";
        }
        return;
    }
}

inline bool StringFrom::Separa(string &A, string &B, string &Orig)
{
    unsigned long long TabPos = Orig.find("\t");
    unsigned long long TabPos2 = Orig.find("\n");
    if (TabPos2 == string::npos){
        A = Orig;
        return 1;
    }
    if (TabPos == string::npos || TabPos > TabPos2)
    {
        A = Orig.substr(0, TabPos2);
        TabPos = 0;
        TabPos2 = TabPos2 + 1;
    }
    else
    {
        int TabPos3 = Orig.find("\t", TabPos+1);
        while (TabPos3 - TabPos == 1)
        {
            TabPos = TabPos3;
            TabPos3 = Orig.find("\t", TabPos + 1);
        }
        A = Orig.substr(0, TabPos + 1);
        Orig.erase(0, TabPos + 1);
        B = Orig.substr(0, TabPos2 - TabPos - 1);
    }
    Orig.erase(0, TabPos2 - TabPos);
    return 0;

}

inline string StringFrom::AlteraCaracteresPor(string A, string Chars, string CharsPara)
{
    int B, B_2;
    while (Chars.find("|") != string::npos)
    {
        B = Chars.find("|");
        string CharA = Chars.substr(0, B);
        B = CharsPara.find("|");
        string CharB = CharsPara.substr(0, B);
        Chars.erase(0, CharA.size() + 1);
        CharsPara.erase(0, CharB.size() + 1);
        while (A.find(CharA) != string::npos)
        {
            string AA, DA;
            B_2 = A.find(CharA);
            AA = A.substr(0, B_2);
            DA = A.substr(B_2 + CharA.size(), A.size());
            A = AA + CharB + DA;
        }
    }
    return A;
}

inline int StringFrom::ContaCaracteres(string A, string Chars)
{
    int Qtd = 0;
    while (Chars.find("|") != string::npos && A != "")
    {
        int B = Chars.find("|");
        string CharA = Chars.substr(0, B);
        Chars.erase(0, CharA.size() + 1);
        while (A.find(CharA) != string::npos)
        {
            string AA, DA;
            int B_2 = A.find(CharA);
            AA = A.substr(0, B_2);
            DA = A.substr(B_2 + CharA.size(), A.size());
            A = AA + DA;
            Qtd++;
        }
    }
    Chars = ",|;| |(|)|!|?|'|&|.|-|";
    while (Chars.find("|") != string::npos && A != "")
    {
        int B = Chars.find("|");
        string CharA = Chars.substr(0, B);
        Chars.erase(0, CharA.size() + 1);
        while (A.find(CharA) != string::npos)
        {
            string AA, DA;
            int B_2 = A.find(CharA);
            AA = A.substr(0, B_2);
            DA = A.substr(B_2 + CharA.size(), A.size());
            A = AA + DA;
            Qtd++;
        }
    }
    return Qtd;
}

void StringFrom::remove(string &S, int i, int j)
{
    if (i < 0)
        i = 0;
    string Aux1 = S.substr(0, i);
    string Aux2 = S.substr(j, S.size());
    string Aux3 = Aux1 + Aux2;
    S.erase(0, S.size());
    for (i = 0; Aux3[i] == ' ' || Aux3[i] == ';'; i++);
    S = Aux3.substr(i, Aux3.size());
}

bool StringFrom::IdiomaValido(string Ling)
{
    string Validos = "EN|GE|IT|PT|RU";
    return Validos.find(Ling) != string::npos;
}

void StringFrom::Converte(string Prim, string Seg, string S, string &A)
{
    S += "\n";
    while (true)
    {
        string Primeira, Segunda;
        bool contagem = StringFrom::Separa(Primeira, Segunda, S);
        if (contagem)
            return;
        StringFrom::ConvertePara(Prim, Primeira, A);
        StringFrom::ConvertePara(Seg, Segunda, A);
        A += "\n";
    }
}

QString StringFrom::ConverteParaAscii(string Ling, string S)
{
    if (Ling == "PT" || Ling == "IT" || Ling == "EN")
        return QString::fromStdString(S);
    if (Ling == "GE")
        return QString::fromStdString(StringFrom::AlteraCaracteresPor(S, "ß|", "á|"));
    if (Ling == "RU")
        return QString::fromStdString(StringFrom::AlteraCaracteresPor(S, "а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я|",
                                   "à|á|â|ã|ä|å|½|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|÷|ø|ù|ú|û|ü|ý|þ|ÿ|À|Á|Â|Ã|Ä|Å|¼|Æ|Ç|È|É|Ê|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|×|Ø|Ù|Ú|Û|Ü|Ý|Þ|ß|"));
}

string StringFrom::StringComparavel(string A, string Ling)
{
    if (Ling == "EN")
        return StringFrom::AlteraCaracteresPor(A, "A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|");
    if (Ling == "GE")
        return StringFrom::AlteraCaracteresPor(A, "A|Ä|B|C|D|E|F|G|H|I|J|K|L|M|N|O|Ö|P|Q|R|S|T|U|Ü|V|W|X|Y|Z|", "a|ä|b|c|d|e|f|g|h|i|j|k|l|m|n|o|ö|p|q|r|s|t|u|ü|v|w|x|y|z|");
    if (Ling == "IT")
        return StringFrom::AlteraCaracteresPor(A, "A|À|B|C|D|E|È|É|F|G|H|I|Ì|J|K|L|M|N|O|Ò|P|Q|R|S|T|U|Ù|V|W|X|Y|Z|", "a|à|b|c|d|e|è|é|f|g|h|i|ì|j|k|l|m|n|o|ò|p|q|r|s|t|u|ù|v|w|x|y|z|");
    if (Ling == "PT")
        return StringFrom::AlteraCaracteresPor(A, "A|À|Á|Ã|Â|B|C|D|E|É|Ê|F|G|H|I|Í|J|K|L|M|N|O|Ó|Õ|Ô|P|Q|R|S|T|U|Ú|Ü|V|W|X|Y|Z|", "a|à|á|ã|â|b|c|d|e|é|ê|f|g|h|i|í|j|k|l|m|n|o|ó|õ|ô|p|q|r|s|t|u|ú|ü|v|w|x|y|z|");
    if (Ling == "RU")
        return StringFrom::AlteraCaracteresPor(A, "А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я|", "а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|");
    return A;
}

int StringFrom::ComparaStrings(string A, string B, string Ling)
{
    A = StringFrom::StringComparavel(A, Ling);
    B = StringFrom::StringComparavel(B, Ling);
    if (Ling == "GE")
    {
        A = StringFrom::AlteraCaracteresPor(A, "ä|ö|ü|ß|", "a|o|u|ss|");
        B = StringFrom::AlteraCaracteresPor(B, "ä|ö|ü|ß|", "a|o|u|ss|");
    }
    if (Ling == "IT")
    {
        A = StringFrom::AlteraCaracteresPor(A, "à|è|é|ì|ò|ù|", "a|e|e|i|o|u|");
        B = StringFrom::AlteraCaracteresPor(B, "à|è|é|ì|ò|ù|", "a|e|e|i|o|u|");
    }
    if (Ling == "PT")
    {
        A = StringFrom::AlteraCaracteresPor(A, "à|á|ã|â|é|ê|í|ó|õ|ô|ú|ç|", "a|a|a|a|e|e|i|o|o|o|u|c|");
        B = StringFrom::AlteraCaracteresPor(B, "à|á|ã|â|é|ê|í|ó|õ|ô|ú|ç|", "a|a|a|a|e|e|i|o|o|o|u|c|");
    }
    if (Ling == "RU")
    {
        A = StringFrom::AlteraCaracteresPor(A, "ё|", "е|");
        B = StringFrom::AlteraCaracteresPor(B, "ё|", "е|");
    }
    if (A > B)
        return 1;
    if (A == B)
        return 0;
    if (A < B)
        return -1;

}

int StringFrom::QuantidadeCaracteres(string A, string Ling)
{
    if (Ling == "EN")
        return StringFrom::ContaCaracteres(A, "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|");
    if (Ling == "GE")
        return StringFrom::ContaCaracteres(A, "a|ä|b|c|d|e|f|g|h|i|j|k|l|m|n|o|ö|p|q|r|s|ß|t|u|ü|v|w|x|y|z|A|Ä|B|C|D|E|F|G|H|I|J|K|L|M|N|O|Ö|P|Q|R|S|T|U|Ü|V|W|X|Y|Z|");
    if (Ling == "IT")
        return StringFrom::ContaCaracteres(A, "a|à|b|c|d|e|è|é|f|g|h|i|ì|j|k|l|m|n|o|ò|p|q|r|s|t|u|ù|v|w|x|y|z|A|À|B|C|D|E|È|É|F|G|H|I|Ì|J|K|L|M|N|O|Ò|P|Q|R|S|T|U|Ù|V|W|X|Y|Z|");
    if (Ling == "PT")
        return StringFrom::ContaCaracteres(A, "a|à|á|ã|â|b|c|ç|d|e|é|ê|f|g|h|i|í|j|k|l|m|n|o|ó|õ|ô|p|q|r|s|t|u|ú|ü|v|w|x|y|z|A|À|Á|Ã|Â|B|C|Ç|D|E|É|Ê|F|G|H|I|Í|J|K|L|M|N|O|Ó|Õ|Ô|P|Q|R|S|T|U|Ú|Ü|V|W|X|Y|Z|");
    if (Ling == "RU")
        return StringFrom::ContaCaracteres(A, "а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я|");
}

bool StringFrom::EProibido(string A, string Ling)
{
    string Procura = ",; ()!?'&.-";
    if (Ling == "EN")
        Procura += "abcdefghijklmnoprqstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (Ling == "GE")
        Procura += "aäbcdefghijklmnoöpqrsßtuüvwxyzAÄBCDEFGHIJKLMNOÖPQRSTUÜVWXYZ";
    if (Ling == "IT")
        Procura += "aàbcdeèéfghiìjklmnoòpqrstuùvwxyzAÀBCDEÈÉFGHIÌJKLMNOÒPQRSTUÙVWXYZ";
    if (Ling == "PT")
        Procura += "aàáãâbcçdeéêfghiíjklmnoóõôpqrstuúüvwxyzAÀÁÃÂBCÇDEÉÊFGHIÍJKLMNOÓÕÔPQRSTUÚÜVWXYZ";
    if (Ling == "RU")
        Procura += "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    return (Procura.find(A) == string::npos);
}

bool StringFrom::NaoPodeEstarNaFrente(string A)
{
    string NaoPodem = " ,.;!?&'()";
    return (NaoPodem.find(A) != string::npos);
}

bool StringFrom::NaoPodeEstarAtras(string A)
{
    string NaoPodem = " ,;&";
    return (NaoPodem.find(A) != string::npos);
}

bool StringFrom::ESubstring(string A, string &B, bool Remover, string Ling)
{
    A = StringFrom::StringComparavel(A, Ling);
    int i, j, k, l, m, in = 0, LimpoAntes, LimpoDepois;
    for (i = 0; i + A.size() <= B.size(); i++)
    {
        string Compara;
        for (j = i; (j - i) < A.size(); j++)
            Compara += B[j];
        if (A == StringFrom::StringComparavel(Compara, Ling))
        {
            LimpoAntes = 1;
            for (k = i - 1; k >= 0 && LimpoAntes; k--)
                if (B[k] != ' ')
                    if (B[k] == ';')
                        break;
                    else
                        LimpoAntes = 0;
            if (LimpoAntes)
            {
                LimpoDepois = 1;
                for (l = j; l < B.size() && LimpoDepois; l++)
                    if (B[l] != ' ')
                        if (B[l] == ';')
                            break;
                        else
                            LimpoDepois = 0;
                if (LimpoDepois)
                {
                    if (Remover)
                        remove(B, k, l);
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool StringFrom::PalavrasSubstring(string &A, string &B, string Ling, bool Remover, int &Contagem)
{
    bool existe = 0;
    string Aux2;
    while (A[0] == ' ' || A[0] == ';')
        A.erase(0, 1);
    do
    {
        int t;
        if (A.find(";") != string::npos)
            t = A.find(";");
        else
            t = A.size();
        string Aux = A.substr(0, t);
        A.erase(0, t);
        while (Aux[0] == ' ')
            Aux.erase(0, 1);
        while (Aux[Aux.size() - 1] == ' ')
            Aux.erase(Aux.size() - 1, 1);
        if (StringFrom::ESubstring(Aux, B, Remover, Ling))
        {
            existe = 1;
            if (Remover)
                Contagem++;
        }
        else
            Aux2 = Aux2 + Aux + "; ";
        while (A[0] == ' ' || A[0] == ';')
            A.erase(0, 1);
    }while (A.size() != 0 && B.size() != 0);
    A = Aux2;
    return existe;
}

void StringFrom::InverteOrdemVetor(vector <string> &A, vector <string> B, string Ling)
{
    vector <string> A_complement;
    string K, KA, KB;
    //char lf = 10;
    unsigned long long fn, fn2;
    for (int i = 0; i < B.size(); i++)
    {
        K = B[i];
        while (K[0] == ' ')
            K.erase(0, 1);
        fn = K.find('\t');
        KA = K.substr(0, fn);
        fn = -1;
        do
        {
            fn = K.find('\t', fn+1);
            fn2 = K.find('\t', fn+1);
        } while (fn2 != string::npos);
        KB = ";";
        if (fn != string::npos)
            KB = K.substr(fn+1, string::npos);
        while (KB.size())
        {
            while (KB[0] == ' ' || KB[0] == ';')
                KB.erase(0, 1);
            if (KB.find(";") == string::npos)
                fn = KB.size();
            else
                fn = KB.find(";");
            string KC = KB.substr(0, fn);
            KB.erase(0, fn);
            int u = A.size(), Bin = 0, Bfn = A.size() - 1, Mt;
            while (Bin < Bfn)
            {
                Mt = (Bin + Bfn)/2;
                int resp = StringFrom::ComparaStrings(A[Mt], KC, Ling);
                if (resp > 0)
                    Bfn = Mt;
                else
                {
                    Bin = Mt + 1;
                    if (!resp)
                        break;
                }
            }
            if (u && StringFrom::ComparaStrings(A[Bin], KC, Ling) < 0)
                Bin++;
            A.insert(A.begin() + Bin, KC);
            A_complement.insert(A_complement.begin() + Bin, KA);
            if (Bin > 0 && KC != "" && StringFrom::ComparaStrings(A[Bin], A[Bin-1], Ling) == 0)
            {
                A.erase(A.begin() + Bin);
                A_complement[Bin-1] = A_complement[Bin-1] + "; " + A_complement[Bin];
                A_complement.erase(A_complement.begin() + Bin);
            }
        }
    }
    for (int i = 0; i < A.size(); i++)
    {
        if (A_complement[i] != "")
            A[i]+= ("\t" + A_complement[i]);
    }
}
