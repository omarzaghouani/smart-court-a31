QT       += core gui  sql network multimedia multimediawidgets charts printsupport widgets axcontainer




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QT += sql
QT += serialport
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = Atelier_Connexion
TEMPLATE = app
SOURCES += \
    arduino.cpp \
    calendrier.cpp \
    connection.cpp \
    juje.cpp \
    login.cpp \
    mail.cpp \
    mailsmtp.cpp \
    main.cpp \
    mainwindow.cpp \
    statistique.cpp \
    window.cpp

HEADERS += \
    WebAxWidget.h \
    arduino.h \
    calendrier.h \
    connection.h \
    juje.h \
    login.h \
    mail.h \
    mailsmtp.h \
    mainwindow.h \
    statistique.h \
    window.h

FORMS += \
    login.ui \
    mainwindow.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += printsupport
QTPLUGIN += windowsprintersupport

RESOURCES += \
    qml.qrc \
    rsc.qrc
 qml.qrc

DISTFILES += \
    map.qml
