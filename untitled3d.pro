QT       += core gui
QT += printsupport
QT += multimedia
QT+=sql
QT += charts
QT       += core gui \
    quick
QT += sql
config += consol
QT += serialport
QT+=serialport
QT += widgets texttospeech
requires(qtHaveModule(gui))
qtHaveModule(gui): requires(qtConfig(combobox))
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG +=c++11
CONFIG += c++17



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affaire.cpp \
    arduino.cpp \
    audiolevel.cpp \
    connection.cpp \
    connexion.cpp \
    juge.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow1.cpp

HEADERS += \
    affaire.h \
    arduino.h \
    audiolevel.h \
    connection.h \
    connexion.h \
    juge.h \
    login.h \
    mainwindow.h \
    mainwindow1.h

FORMS += \
    login.ui \
    mainwindow.ui \
    mainwindow1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc \
    rsc.qrc

DISTFILES += \
    PdfList.pdf \
    gestion_contrat.pro.user \
    gestion_contrat.pro.user.bd8a8ce

SUBDIRS += \
    gestion_contrat.pro
