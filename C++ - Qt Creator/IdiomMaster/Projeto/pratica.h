#ifndef PRATICA_H
#define PRATICA_H

#include <QDialog>
#include <vector>
#include <string>
#include <set>
#include "dicionario.h"
#include "mapateclado.h"

struct Kt{
    int Indice;
    int TempoRestante;
};

namespace Ui {
class Pratica;
}

class Pratica : public QDialog
{
    Q_OBJECT

public:
    explicit Pratica(QWidget *parent = 0);
    ~Pratica();
    //bool ImportarDeArquivo(QString EnderecoArquivo);
    void Parametro(string Langfrom, string Langto, int nivel, Dicionario *Dic);
    void setLinha(string Lista, string Origem);
    void setRefDicionario(int idxDicionario);
    void rodar();
    bool todasPraticadas();

private slots:
    void on_proximo_pressed();
    void on_submeter_pressed();
    //void on_salvar_pressed();
    void on_opcoes_pressed();
    void on_PalavraASubmeter_textChanged();
    void on_PalavraASubmeter_editingFinished();
    void on_tela1_clicked();
    void on_tela2_clicked();

private:
    Ui::Pratica *ui;
    Dicionario *Dic;
    int TelaAtual, TelaAtualAtual;
    vector <int> refDicionario;
    vector <string> List[2];
    vector <string> Src[2];
    vector <int> ListInd[2];
    vector <Kt> KataInd[2];
    vector <int> SetarEliminadas[2];
    string Lf;
    string Lt;
    bool KataAutoSetavel, inicializavel;
    int IndAtual[2];
    int Linha[2], Coluna[2];
    int N[2];
    int checado;
    int nivel;
    int StrAnterior;
    int QTPalavras[2];
    int QTTraduzidas[2];
    enum coluna {ORIGEM, TRADU, ORIGEM2, TRADU2};
    MapaTeclado MT;
    inline string getPrimeira(string A);
    inline string getSegunda(string A);
    void setSegunda(string A);
    void inserirKata();
    void submetePalavra(string Palavra);
    int getPalavraKata();
    void setPalavraKata();
    void estiloTraduzir(int Ind);
    void estiloTraduzindo();
    void estiloTraduzido();
    void selecionaRow(int Ind, bool M);
    int PalavraSubstring(string A);
    void ConfiguraTempoKata(int Ind);
    int contaPalavras(string S);
    bool Importa(string Str);
    void Exporta(QString Nome);
    void resizeEvent(QResizeEvent *event);
    void DesabilitaOuHabilitaJanela();
    void AtualizaInfo();
};

#endif // PRATICA_H
