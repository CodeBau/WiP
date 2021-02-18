QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Source/accont_data_change.cpp \
    Source/api_process.cpp \
    Source/config.cpp \
    Source/config_e.cpp \
    Source/hash.cpp \
    Source/hash_e.cpp \
    Source/loginphase.cpp \
    Source/logs.cpp \
    Source/logwin.cpp \
    Source/main.cpp \
    Source/mainwin.cpp \
    Source/pswdrmdwin.cpp \
    Source/regwin.cpp

HEADERS += \
    Headers/accont_data_change.h \
    Headers/api_process.h \
    Headers/config.h \
    Headers/config_e.h \
    Headers/fragile.h \
    Headers/fragile_e.h \
    Headers/hash.h \
    Headers/hash_e.h \
    Headers/loginphase.h \
    Headers/logs.h \
    Headers/logwin.h \
    Headers/mainwin.h \
    Headers/pswdrmdwin.h \
    Headers/regwin.h \
    Headers/window_init.h

FORMS += \
    Forms/accont_data_change.ui \
    Forms/logwin.ui \
    Forms/mainwin.ui \
    Forms/pswdrmdwin.ui \
    Forms/regwin.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  resource.qrc
