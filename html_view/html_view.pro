TARGET       = html_view
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
CONFIG += c++11
#CONFIG      += create_prl

INCLUDEPATH += ./ \
               ../object_registry/ \
               ../command_registry \
               ../command_registry_ex \
               ../../evo/storage_base/include \
               ../../base/geogebra \
               ../../base/base/include


SOURCES     += ./*.cpp
HEADERS     += ./*.h

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
