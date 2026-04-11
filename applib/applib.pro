TARGET       = applib
TEMPLATE     = lib
CONFIG      += staticlib
#######################################################################################
wasm {
    CONFIG(debug, debug|release): SOURCEDIR = debug_wasm
    else:                         SOURCEDIR = release_wasm
} else {
    CONFIG(debug, debug|release): SOURCEDIR = debug
    else:                         SOURCEDIR = release
}
DESTDIR = $$PWD/../../BUILD/$$TARGET/$$SOURCEDIR

SOURCES     += $$PWD/src/*.cpp
HEADERS     += $$PWD/include/*.h

INCLUDEPATH += $$PWD//include
INCLUDEPATH += $$PWD/../../cad_professional/cad_professional_lib
INCLUDEPATH += $$PWD/../../evo/evo_signal
INCLUDEPATH += $$PWD/../../evo/cad
INCLUDEPATH += $$PWD/../../evo/cad_infrastructure
INCLUDEPATH += $$PWD/../../evo/storage
INCLUDEPATH += $$PWD/../../hg/hg_interact
INCLUDEPATH += $$PWD/../../hg/hg_display
INCLUDEPATH += $$PWD/../../hg/hg_papper
INCLUDEPATH += $$PWD/../../hg/hg_style
INCLUDEPATH += $$PWD/../../hg/hg_utility/include
INCLUDEPATH += $$PWD/../../hg/hg_text
INCLUDEPATH += $$PWD/../../evo/storage_base/include
INCLUDEPATH += $$PWD/../../evo/storage
INCLUDEPATH += $$PWD/../../infrastructure/command_registry
INCLUDEPATH += $$PWD/../../infrastructure/command_registry_ex
INCLUDEPATH += $$PWD/../../infrastructure/object_registry
!wasm {
INCLUDEPATH += $$PWD/../../infrastructure/html_view
}
INCLUDEPATH += $$PWD/../../infrastructure/licence/include
INCLUDEPATH += $$PWD/../../base/geogebra
INCLUDEPATH += $$PWD/../../base/base/include
INCLUDEPATH += $$PWD/../../infrastructure/applib/include
INCLUDEPATH += $$PWD/../../evo/route_draw
INCLUDEPATH += $$PWD/../../evo/cad_draw

UNIVERSEDIR = $$PWD/../../../../data/1302_FLOW/packages/1302_datafromsky_trafficengine/app/common/universe
INCLUDEPATH += $$UNIVERSEDIR/cmd_sys

INCLUDEPATH += $$UNIVERSEDIR/base
INCLUDEPATH += $$UNIVERSEDIR/utility
INCLUDEPATH += $$UNIVERSEDIR/universe_server_shared

QT += widgets

DISTFILES += \
    .gitignore
