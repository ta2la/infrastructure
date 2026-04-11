TARGET       = command_registry_ex
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
wasm {
    CONFIG(debug, debug|release): SOURCEDIR = debug_wasm
    else:                         SOURCEDIR = release_wasm
} else {
    CONFIG(debug, debug|release): SOURCEDIR = debug
    else:                         SOURCEDIR = release
}
DESTDIR = $$PWD/../../BUILD/$$TARGET/$$SOURCEDIR

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
