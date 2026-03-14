TARGET      = object_registry
TEMPLATE    = lib
CONFIG     += staticlib
#######################################################################################
CONFIG += c++11
DESTDIR = $$PWD/debug

INCLUDEPATH += $$PWD/include

SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

