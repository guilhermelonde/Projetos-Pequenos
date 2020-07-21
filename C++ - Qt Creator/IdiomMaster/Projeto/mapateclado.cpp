#include "mapateclado.h"
#include "ui_mapateclado.h"
#include "string"
#include "mapearcaracter.h"

MapaTeclado::MapaTeclado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapaTeclado)
{
    ui->setupUi(this);
    PodeEditar = 0;
}

MapaTeclado::~MapaTeclado()
{
    delete ui;
}

void MapaTeclado::Inicializa(string Para)
{
    setWindowTitle("Mapear caracteres do teclado");
    string TituloA, TituloB;
    TituloB = "caracter chave";
    string alfabeto;
    if (Para == "EN")
    {
        TituloA = "Caracter inglês";
        alfabeto = "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|";
    }
    if (Para == "GE")
    {
        TituloA = "Caracter alemão";
        alfabeto = "a|ä|b|c|d|e|f|g|h|i|j|k|l|m|n|o|ö|p|q|r|s|ß|t|u|ü|v|w|x|y|z|A|Ä|B|C|D|E|F|G|H|I|J|K|L|M|N|O|Ö|P|Q|R|S|T|U|Ü|V|W|X|Y|Z|";
    }
    if (Para == "IT")
    {
        TituloA = "Caracter italiano";
        alfabeto = "a|à|b|c|d|e|è|é|f|g|h|i|ì|j|k|l|m|n|o|ò|p|q|r|s|t|u|ù|v|w|x|y|z|A|À|B|C|D|E|È|É|F|G|H|I|Ì|J|K|L|M|N|O|Ò|P|Q|R|S|T|U|Ù|V|W|X|Y|Z|";
    }
    if (Para == "PT")
    {
        TituloA = "Caracter português";
        alfabeto = "a|à|á|ã|â|b|c|ç|d|e|é|ê|f|g|h|i|í|j|k|l|m|n|o|ó|õ|ô|p|q|r|s|t|u|ú|ü|v|w|x|y|z|A|À|Á|Ã|Â|B|C|Ç|D|E|É|Ê|F|G|H|I|Í|J|K|L|M|N|O|Ó|Õ|Ô|P|Q|R|S|T|U|Ú|Ü|V|W|X|Y|Z|";
    }
    if (Para == "RU")
    {
        TituloA = "Caracter russo";
        alfabeto = "а|б|в|г|д|е|ё|ж|з|и|й|к|л|м|н|о|п|р|с|т|у|ф|х|ц|ч|ш|щ|ъ|ы|ь|э|ю|я|А|Б|В|Г|Д|Е|Ё|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я|";
    }
    ui->IdiomOrig->setText(QString::fromStdString(TituloB));
    ui->IdiomTradu->setText(QString::fromStdString(TituloA));
    SetNew(alfabeto);
    PodeEditar = 1;
}

bool MapaTeclado::listaDeOpcoes(string k, int x, int y)
{
    vector <int> achados;
    for (int it = 0; it < Mapa.size(); it++)
        if (ui->tabela->item(Mapa[it], 1)->text().toStdString() == k)
            achados.push_back(Mapa[it]);
    if (achados.size() != 0)
    {
        elemento = ui->tabela->item(achados[0], 0)->text().toStdString();
        return true;
    }
    else
        return false;
}

string MapaTeclado::getElemento()
{
    return elemento;
}

void MapaTeclado::SetNew(string Idioma)
{
    for (int i = 0; Idioma.find("|") != string::npos; i++)
    {
        int virg = Idioma.find("|");
        string ChA = Idioma.substr(0, virg);
        Idioma.erase(0, virg + 1);
        ui->tabela->insertRow(i);
        ui->tabela->setItem(i, ORIGEM, new QTableWidgetItem(QString::fromStdString(ChA)));
        ui->tabela->setItem(i, CHAVE, new QTableWidgetItem(""));
        ui->tabela->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tabela->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
}

void MapaTeclado::on_pushButton_pressed()
{
    this->close();
}

void MapaTeclado::on_tabela_cellActivated(int row, int column)
{
    if (PodeEditar)
    {
        string chave;
        string E = ui->tabela->item(row, 0)->text().toStdString();
        bool Mapeou;
        MapearCaracter MC;
        MC.setModal(true);
        MC.Parametro(E, &chave, &Mapeou);
        MC.exec();
        if (Mapeou)
        {
            ui->tabela->item(row, 1)->setText(QString::fromStdString(chave));
            Mapa.push_back(row);
        }
        else
        {
            ui->tabela->item(row, 1)->setText("");
            for (int i = 0; i < Mapa.size(); i++)
                if (Mapa[i] == row)
                {
                    Mapa.erase(Mapa.begin() + i);
                    return;
                }
        }
        ui->tabela->clearSelection();
    }
}
