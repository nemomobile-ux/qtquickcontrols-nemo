set(PACKAGE nemocoreplugin)

set(SRC
    nemoimageprovider.cpp
    plugin.cpp
    themedaemon/mlocalthemedaemonclient.cpp
    themedaemon/mabstractthemedaemonclient.cpp
    theme.cpp
    logging.cpp)

set(HEADERS
    nemoimageprovider.h
    plugin.h
    logging.h
    themedaemon/mlocalthemedaemonclient.h
    themedaemon/mabstractthemedaemonclient.h)

set(PUBLIC_HEADERS
    theme.h)

add_library(${PACKAGE} SHARED ${SRC} ${MLITE})
add_definitions( -DQT_INSTALL_QML="${QT_INSTALL_QML}")

qt6_add_qml_module(${PACKAGE}
    URI Nemo
    VERSION 2.0
    PLUGIN_TARGET ${PACKAGE}
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${SOURCES}
        ${HEADERS}
        ${PUBLIC_HEADERS}
    QML_FILES
        ${QML}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Nemo
)

target_link_libraries(${PACKAGE} PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    PkgConfig::MLITE)

configure_file(${PACKAGE}.pc.in ${PACKAGE}.pc @ONLY)

install(TARGETS ${PACKAGE}
    RUNTIME DESTINATION "${QT_INSTALL_QML}/Nemo/"
    BUNDLE DESTINATION "${QT_INSTALL_QML}/Nemo/"
    LIBRARY DESTINATION "${QT_INSTALL_QML}/Nemo/"
)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nemocontrols/core/)

install(FILES qmldir
    DESTINATION ${QT_INSTALL_QML}/Nemo/)

install(FILES nemo.json
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/themes/)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
