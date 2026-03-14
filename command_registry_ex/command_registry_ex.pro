TARGET       = command_registry_ex
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

INCLUDEPATH += $$PWD/ \
               $$PWD/../command_registry

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

QT += widgets
