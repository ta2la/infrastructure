TARGET    = command_registry
TEMPLATE  = lib
CONFIG    += staticlib
#######################################################################################
CONFIG += c++11
#CONFIG   += create_prl
wasm {
    CONFIG(debug, debug|release): SOURCEDIR = debug_wasm
    else:                         SOURCEDIR = release_wasm
} else {
    CONFIG(debug, debug|release): SOURCEDIR = debug
    else:                         SOURCEDIR = release
}
DESTDIR = $$PWD/../../BUILD/$$TARGET/$$SOURCEDIR

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

