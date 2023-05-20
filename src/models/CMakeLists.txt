set(SRC
    calendarmodel.cpp
    plugin.cpp)

set(HEADERS
    calendarmodel.h
    plugin.h)

add_library(nemomodels SHARED ${SRC})

qt6_add_qml_module(nemomodels
    URI Nemo.Models
    VERSION 2.0
    PLUGIN_TARGET nemomodels
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${SOURCES}
        ${HEADERS}
    QML_FILES
        ${QML}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Nemo/Models
)


target_link_libraries(nemomodels PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
)

install(FILES qmldir DESTINATION ${QT_INSTALL_QML}/Nemo/Models/)
install(TARGETS nemomodels DESTINATION ${QT_INSTALL_QML}/Nemo/Models/)
