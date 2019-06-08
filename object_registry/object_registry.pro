TEMPLATE    = lib
CONFIG     += staticlib
TARGET      = object_registry
#CONFIG       += create_prl

INCLUDEPATH += ./include

SOURCES     += ./*.cpp
HEADERS     += ./*.h

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}

