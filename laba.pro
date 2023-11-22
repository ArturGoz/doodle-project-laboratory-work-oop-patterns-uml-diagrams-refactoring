QT       += core gui



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -L"..\SFML-2.6.0\lib"
LIBS += -L"..\SFML-2.6.0\bin"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window

INCLUDEPATH += "..\SFML-2.6.0\include"

DEPENDPATH += "..\SFML-2.6.0\include"

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    tutorial.cpp

HEADERS += \
    doodle.h \
    mainwindow.h \
    settings.h \
    tutorial.h

FORMS += \
    mainwindow.ui \
    settings.ui \
    tutorial.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
