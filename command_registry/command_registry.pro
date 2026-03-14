TARGET    = command_registry
TEMPLATE  = lib
CONFIG    += staticlib
#######################################################################################
CONFIG += c++11
#CONFIG   += create_prl
DESTDIR = $$PWD/debug

INCLUDEPATH += $$PWD/

SOURCES += $$PWD/*.cpp
HEADERS += $$PWD/*.h

QT -= core

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

