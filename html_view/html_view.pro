TARGET       = html_view
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
#CONFIG      += create_prl
wasm {
    CONFIG(debug, debug|release): SOURCEDIR = debug_wasm
    else:                         SOURCEDIR = release_wasm
} else {
    CONFIG(debug, debug|release): SOURCEDIR = debug
    else:                         SOURCEDIR = release
}
DESTDIR = $$PWD/../../BUILD/$$TARGET/$$SOURCEDIR

INCLUDEPATH += $$PWD \
               $$PWD/../object_registry/ \
               $$PWD/../command_registry \
               $$PWD/../command_registry_ex \
               $$PWD/../../evo/storage_base/include \
               $$PWD/../../base/geogebra \
               $$PWD/../../base/base/include


SOURCES     += $$PWD/*.cpp
HEADERS     += $$PWD/*.h

QT += widgets

#win32 {
#    DEFINES += WINDOWS
#    QT += webengine webenginewidgets
#}
#else:linux {
#    QT += webkit webkitwidgets
#}

CONFIG(debug, debug|release) {
     DEFINES += DEBUG
}
else {
     DEFINES += NDEBUG
}
