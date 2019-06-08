TARGET       = command_registry_ex
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11

SOURCES     += ./*.cpp
HEADERS     += ./*.h

INCLUDEPATH += ./ \
               ../command_registry
               #../../base/infrastructure

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

