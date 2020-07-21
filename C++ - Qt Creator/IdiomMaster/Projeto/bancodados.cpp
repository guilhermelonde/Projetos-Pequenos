#include "bancodados.h"

BancoDados::BancoDados()
{
    qb = QSqlDatabase::addDatabase("IdiomMaster");
}
