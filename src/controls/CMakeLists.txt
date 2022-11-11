pkg_check_modules(MLITE mlite5 REQUIRED IMPORTED_TARGET)

set(SRC
    ringindicator.cpp
    qquickfilteringmousearea.cpp
    sizing.cpp
    nemopage.cpp
    qrc_internal_resources.cpp
    nemoimageprovider.cpp
    qquicknemocontrolsextensionplugin.cpp
    themedaemon/mlocalthemedaemonclient.cpp
    themedaemon/mabstractthemedaemonclient.cpp
    editfilter.cpp
    theme.cpp
    nemofocussingleton.cpp
    nemowindow.cpp
)

set(HEADERS
    editfilter.h
    theme.h
    ringindicator.h
    nemoimageprovider.h
    qquicknemocontrolsextensionplugin.h
    themedaemon/mlocalthemedaemonclient.h
    themedaemon/mabstractthemedaemonclient.h
    qquickfilteringmousearea.h
    nemofocussingleton.h
    nemowindow.h
    sizing.h
    nemopage.h
)

add_library(nemocontrolsplugin SHARED ${SRC} ${MLITE})

set(QT_LIB_LIST Core Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

target_link_libraries(nemocontrolsplugin
    ${QT_DEPLIBS}
    PkgConfig::MLITE)

install(DIRECTORY qml DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Nemo/)
install(TARGETS nemocontrolsplugin DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Nemo/)

install(DIRECTORY qml/
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Nemo/
        PATTERN "dialogs" EXCLUDE)
        
install(DIRECTORY qml/dialogs/
        DESTINATION ${QT_INSTALL_QML}/Nemo/Dialogs)

install(DIRECTORY images
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Nemo)