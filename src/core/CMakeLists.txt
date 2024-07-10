set(SRC
    sizing.cpp
    nemoimageprovider.cpp
    plugin.cpp
    themedaemon/mlocalthemedaemonclient.cpp
    themedaemon/mabstractthemedaemonclient.cpp
    theme.cpp
    logging.cpp)

set(HEADERS
    nemoimageprovider.h
    plugin.h
    sizing.h
    theme.h
    logging.h
    themedaemon/mlocalthemedaemonclient.h
    themedaemon/mabstractthemedaemonclient.h)

add_library(nemocoreplugin SHARED ${SRC} ${MLITE})
add_definitions( -DQT_INSTALL_QML="${QT_INSTALL_QML}")

qt6_add_qml_module(nemocoreplugin
    URI Nemo
    VERSION 2.0
    PLUGIN_TARGET nemocoreplugin
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${SOURCES}
        ${HEADERS}
    QML_FILES
        ${QML}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Nemo
)

target_link_libraries(nemocoreplugin PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    PkgConfig::MLITE)


install(TARGETS nemocoreplugin
    RUNTIME DESTINATION "${QT_INSTALL_QML}/Nemo/"
    BUNDLE DESTINATION "${QT_INSTALL_QML}/Nemo/"
    LIBRARY DESTINATION "${QT_INSTALL_QML}/Nemo/"
)


install(FILES qmldir
    DESTINATION ${QT_INSTALL_QML}/Nemo/)
