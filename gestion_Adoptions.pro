QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += sql
QT += printsupport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    beneficiaire.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    statistique.cpp

HEADERS += \
    beneficiaire.h \
    connection.h \
    mainwindow.h \
    misc.h \
    statistique.h

FORMS += \
    mainwindow.ui \
    statistique.ui

TRANSLATIONS += \
    application_fr_FR.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    translations.qrc
