#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T22:36:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IdiomMasterOLD
TEMPLATE = app


SOURCES += main.cpp\
    arquivo.cpp \
    bancodedados.cpp \
    interacaobd.cpp \
        mainwindow.cpp \
    abrirrotinadearquivo.cpp \
    dicionario.cpp \
    verlista.cpp \
    stringfrom.cpp \
    niveldificuldade.cpp \
    verlistaselecao.cpp \
    pratica.cpp \
    caixaopcoespraticar.cpp \
    mapateclado.cpp \
    mapearcaracter.cpp \
    entrardicionario.cpp \
    sairsemsalvar.cpp \
    novapalavra.cpp \
    celulatabela.cpp \
    exibetraducoesrealizadas.cpp \
    modoedicao.cpp

HEADERS  += mainwindow.h \
    abrirrotinadearquivo.h \
    arquivo.h \
    bancodedados.h \
    dicionario.h \
    interacaobd.h \
    verlista.h \
    stringfrom.h \
    niveldificuldade.h \
    verlistaselecao.h \
    pratica.h \
    caixaopcoespraticar.h \
    mapateclado.h \
    mapearcaracter.h \
    entrardicionario.h \
    sairsemsalvar.h \
    novapalavra.h \
    celulatabela.h \
    exibetraducoesrealizadas.h \
    modoedicao.h \
    janelasedicao.h \
    registrobd.h

FORMS    += mainwindow.ui \
    abrirrotinadearquivo.ui \
    verlista.ui \
    niveldificuldade.ui \
    verlistaselecao.ui \
    pratica.ui \
    caixaopcoespraticar.ui \
    mapateclado.ui \
    mapearcaracter.ui \
    entrardicionario.ui \
    sairsemsalvar.ui \
    novapalavra.ui \
    celulatabela.ui \
    exibetraducoesrealizadas.ui \
    modoedicao.ui

DISTFILES +=

RESOURCES += \
    imagens.qrc
