TARGET    = command_registry
TEMPLATE  = lib
CONFIG    += staticlib
#######################################################################################
CONFIG += c++11
#CONFIG   += create_prl

INCLUDEPATH += ./

SOURCES += ./*.cpp
HEADERS += ./*.h

QT -= core

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

