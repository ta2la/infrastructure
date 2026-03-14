TARGET       = html_view
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
#CONFIG      += create_prl
DESTDIR = $$PWD/debug

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
