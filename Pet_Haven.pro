QT       += core gui
QT       += sql
QT       += printsupport

QT       += serialport
QT       += network
QT       += widgets

QT       += positioning
QT       += location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = smtp
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connexion.cpp \
    main.cpp \
    sources/SwitchButton.cpp \
    sources/adoption.cpp \
    sources/animal.cpp \
    sources/arduino.cpp \
    sources/beneficiaire.cpp \
    sources/employe.cpp \
    sources/livraison.cpp \
    sources/newcalendarwidget.cpp \
    sources/qr.cpp \
    sources/qrcodegen.cpp \
    sources/smtp.cpp \
    sources/statistique_adoptions.cpp \
    sources/statistique_beneficiaires.cpp \
    sources/statistique_dons.cpp \
    sources/dons.cpp \
    mainwindow.cpp

HEADERS += \
    connexion.h \
    headers/adoption.h \
    headers/animal.h \
    headers/arduino.h \
    headers/SwitchButton.h \
    headers/beneficiaire.h \
    headers/employe.h \
    headers/livraison.h \
    headers/newcalendarwidget.h \
    headers/qrcodegen.h \
    headers/smtp.h \
    headers/statistique_adoptions.h \
    headers/statistique_beneficiaires.h \
    headers/statistique_dons.h \
    headers/dons.h \
    mainwindow.h

FORMS += \
    mainwindow.ui \
    statistique_adoptions.ui \
    statistique_beneficiaires.ui \
    statistique_dons.ui

RESOURCES += \
    ressource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
