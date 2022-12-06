QT       += core gui \
    quick
QT += sql
config += consol
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connexion.cpp \
    contrat_client.cpp \
    login.cpp \
    main.cpp \
    mainwindow1.cpp

HEADERS += \
    arduino.h \
    connexion.h \
    contrat_client.h \
    login.h \
    mainwindow1.h

FORMS += \
    login.ui \
    mainwindow1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    rsc/back.png

RESOURCES += \
    rsc.qrc
