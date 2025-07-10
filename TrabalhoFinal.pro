QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    character.cpp \
    characterclass.cpp \
    clericspelllist.cpp \
    creatorscreen.cpp \
    main.cpp \
    mainwindow.cpp \
    species.cpp \
    wizardspelllist.cpp

HEADERS += \
    background.h \
    character.h \
    characterclass.h \
    clericspelllist.h \
    creatorscreen.h \
    mainwindow.h \
    species.h \
    wizardspelllist.h

FORMS += \
    clericspelllist.ui \
    creatorscreen.ui \
    mainwindow.ui \
    wizardspelllist.ui

ICONS += \
    dnd-icon.png

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
