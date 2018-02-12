#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T10:26:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app
CONFIG += c++11
QT += xml
QT += network
CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    aloitapeli.cpp \
    kaupunki.cpp \
    parkkihalli.cpp \
    tilasto.cpp \
    parkkihalliikkuna.cpp \
    phallilogiikka.cpp \
    ruutu.cpp \
    sijainti.cpp \
    este.cpp \
    kaupunkiikkuna.cpp \
    xmlparkkihallireader.cpp \
    laura.cpp \
    toimijaRP.cpp \
    vihollinen.cpp \
    teekkarikyborgi.cpp \
    phallinapufunktiot.cpp \
    lataatiedosto.cpp \
    kauppa.cpp \
    tekoaly.cpp \
    kauppaikkuna.cpp \
    ammus.cpp \
    virheikkuna.cpp \
    ohjeet.cpp \
    parkkihallilopetusikkuna.cpp \
    pelinlopetusikkuna.cpp

HEADERS  += mainwindow.h \
    aloitapeli.h \
    kaupunki.h \
    parkkihalli.h \
    toimijaRP.h \
    tilasto.h \
    parkkihalliikkuna.h \
    phallilogiikka.h \
    ruutu.h \
    sijainti.h \
    este.h \
    kaupunkiikkuna.h \
    xmlparkkihallireader.h \
    laura.h \
    vihollinen.h \
    teekkarikyborgi.h \
    phallinapufunktiot.h \
    lataatiedosto.h \
    kauppa.h \
    tekoaly.h \
    kauppaikkuna.h \
    ammus.h \
    virheikkuna.h \
    ohjeet.h \
    parkkihallilopetusikkuna.h \
    pelinlopetusikkuna.h

FORMS    += mainwindow.ui \
    parkkihalliikkuna.ui \
    kaupunkiikkuna.ui \
    kauppaikkuna.ui \
    virheikkuna.ui \
    ohjeet.ui \
    parkkihallilopetusikkuna.ui \
    pelinlopetusikkuna.ui

RESOURCES += \
    Kuvat.qrc \
    Tiedostot.qrc

OTHER_FILES +=
