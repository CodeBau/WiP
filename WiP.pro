QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source/logs.cpp \
    Source/logwin.cpp \
    Source/main.cpp \
    Source/mainwin.cpp \
    Source/pswdrmdwin.cpp \
    Source/regwin.cpp \

HEADERS += \
    Headers/config.h \
    Headers/config_example.h \
    Headers/logs.h \
    Headers/logwin.h \
    Headers/mainwin.h \
    Headers/pswdrmdwin.h \
    Headers/regwin.h \

FORMS += \
    Forms/logwin.ui \
    Forms/mainwin.ui \
    Forms/pswdrmdwin.ui \
    Forms/regwin.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
