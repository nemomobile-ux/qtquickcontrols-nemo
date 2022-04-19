pkg_check_modules(MLITE mlite5 REQUIRED IMPORTED_TARGET)

set(SRC
    hacks.cpp
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
    hacks.h
    qquickfilteringmousearea.h
    nemofocussingleton.h
    nemowindow.h
    sizing.h
    nemopage.h
)

add_library(nemocontrolsplugin SHARED ${SRC} ${MLITE})

target_link_libraries(nemocontrolsplugin
    Qt5::Core
    Qt5::Qml 
    Qt5::Quick
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
