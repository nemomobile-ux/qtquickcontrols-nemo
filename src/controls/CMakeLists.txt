set(PROJECT nemocontrolsplugin)

set(SRC
    ringindicator.cpp
    filteringmousearea.cpp
    nemopage.cpp
    qrc_internal_resources.cpp
    plugin.cpp
    editfilter.cpp
    nemofocussingleton.cpp
    nemowindow.cpp
    inversemousearea.cpp
    logging.cpp)

set(HEADERS
    editfilter.h
    ringindicator.h
    plugin.h
    filteringmousearea.h
    nemofocussingleton.h
    nemowindow.h
    nemopage.h
    inversemousearea.h
    logging.h)

set(QML
    qml/ActionButton.qml
    qml/ApplicationWindow.qml
    qml/Button.qml
    qml/ButtonRow.qml
    qml/Checkbox.qml
    qml/DatePicker.qml
    qml/ErrorStackPage.qml
    qml/GlacierRollerItem.qml
    qml/GlacierRoller.qml
    qml/Header.qml
    qml/HeaderToolsLayout.qml
    qml/IconButton.qml
    qml/Label.qml
    qml/ListViewItemWithActions.qml
    qml/ListView.qml
    qml/NemoIcon.qml
    qml/Page.qml
    qml/ProgressBar.qml
    qml/ScrollDecorator.qml
    qml/Slider.qml
    qml/Spinner.qml
    qml/TextField.qml
    qml/TabButton.qml
    qml/TimePicker.qml
    qml/ToolButton.qml)

add_library(${PROJECT} SHARED ${SRC} ${MLITE})

qt6_add_qml_module(${PROJECT}
    URI Nemo.Controls
    VERSION 2.0
    PLUGIN_TARGET ${PROJECT}
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${SOURCES}
        ${HEADERS}
    QML_FILES
        ${QML}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Nemo/Controls
)

qt6_add_resources(${PROJECT}
    PREFIX "images"
    FILES
        images/disabled-overlay-inverse.png
        images/disabled-overlay.png
        images/glacierroller-icon-arrow-down.svg
        images/listview-icon-arrow.svg
        images/listview-icon-template-s.svg
        images/no-icon.png
)

target_link_libraries(${PROJECT} PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    PkgConfig::MLITE)

install(TARGETS ${PROJECT}
    RUNTIME DESTINATION "${QT_INSTALL_QML}/Nemo/Controls"
    BUNDLE DESTINATION "${QT_INSTALL_QML}/Nemo/Controls"
    LIBRARY DESTINATION "${QT_INSTALL_QML}/Nemo/Controls"
)

install(DIRECTORY qml/
    DESTINATION ${QT_INSTALL_QML}/Nemo/Controls)

install(DIRECTORY images
    DESTINATION ${QT_INSTALL_QML}/Nemo/Controls)
