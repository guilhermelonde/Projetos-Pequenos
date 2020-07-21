#include "bancodedados.h"
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <iostream>
#include <exception>
#include <QDir>
#include <QDebug>
#include <QSqlRecord>

list<RegistroBD> BancoDeDados::todos()
{
    list<RegistroBD> L;
    QSqlQuery query ("SELECT * FROM " + dic);
    int idA = query.record().indexOf("palOrigem");
    int idB = query.record().indexOf("palDestino");
    int idP = query.record().indexOf("praticada");
    while(query.next()){
        QString A = query.value(idA).toString();
        QString B = query.value(idB).toString();
        int y = query.value(idP).toInt();
        qDebug() << A;
        L.push_back(RegistroBD(A.toStdString(), B.toStdString(), y));
    }
    return L;
}

void BancoDeDados::limpar()
{
    QSqlQuery qry;
    qry.prepare("DELETE FROM " + dic);
    if (!qry.exec())
        qDebug() << "nao deletou";
}

void BancoDeDados::criar(RegistroBD r)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO " + dic + " (palOrigem, palDestino, praticada) VALUES (:a, :b, :p)");
    qry.bindValue(":a", QString::fromStdString(r.A));
    qry.bindValue(":b", QString::fromStdString(r.B));
    qry.bindValue(":p", (int)r.praticado);
    if (!qry.exec())
        qDebug() << "nao inseriu";
}

void BancoDeDados::dicionario(string De, string Para)
{
    this->dic = QString::fromStdString(De + "_" + Para);
    QSqlQuery qry;
    qry.prepare( "CREATE TABLE " + dic + " (palOrigem TEXT PRIMARY KEY, palDestino TEXT, praticada INTEGER);");
    if (!qry.exec())
        qDebug() << "nao criou";
}

BancoDeDados::BancoDeDados()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("dic/idiomMaster.db");
    if (!db.open())
        qDebug() << "falhou";
    else
        qDebug() << "ok";
}

BancoDeDados::~BancoDeDados()
{
    if (db.isOpen())
        db.close();
}
