set(SRC
    ringindicator.cpp
    filteringmousearea.cpp
    nemopage.cpp
    qrc_internal_resources.cpp
    plugin.cpp
    editfilter.cpp
    nemofocussingleton.cpp
    nemowindow.cpp
    )

set(HEADERS
    editfilter.h
    ringindicator.h
    plugin.h
    filteringmousearea.h
    nemofocussingleton.h
    nemowindow.h
    nemopage.h)

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
    qml/HeaderToolsIndicator.qml
    qml/HeaderToolsLayout.qml
    qml/IconButton.qml
    qml/InverseMouseArea.qml
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
    qml/TimePicker.qml
    qml/ToolButton.qml)

add_library(nemocontrolsplugin SHARED ${SRC} ${MLITE})

qt6_add_qml_module(nemocontrolsplugin
    URI Nemo.Controls
    VERSION 2.0
    PLUGIN_TARGET nemocontrolsplugin
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${SOURCES}
        ${HEADERS}
    QML_FILES
        ${QML}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Nemo/Controls
)

qt6_add_shaders(nemocontrolsplugin "shaders"
    BATCHABLE
    PRECOMPILE
    OPTIMIZED
    PREFIX
        "/"
    FILES
        "qml/shaders/NemoIcon.frag"
    )

target_link_libraries(nemocontrolsplugin PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    PkgConfig::MLITE)


install(TARGETS nemocontrolsplugin
    RUNTIME DESTINATION "${QT_INSTALL_QML}/Nemo/Controls"
    BUNDLE DESTINATION "${QT_INSTALL_QML}/Nemo/Controls"
    LIBRARY DESTINATION "${QT_INSTALL_QML}/Nemo/Controls"
)

install(DIRECTORY qml/
    DESTINATION ${QT_INSTALL_QML}/Nemo/Controls)

install(DIRECTORY images
    DESTINATION ${QT_INSTALL_QML}/Nemo/Controls)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/.qsb/qml/shaders
    DESTINATION ${QT_INSTALL_QML}/Nemo/Controls)
