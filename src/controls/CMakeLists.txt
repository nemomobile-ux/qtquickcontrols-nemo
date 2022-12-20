pkg_check_modules(MLITE mlite${QT_MAJOR_VERSION} REQUIRED IMPORTED_TARGET)

set(SRC
    ringindicator.cpp
    qquickfilteringmousearea.cpp
    sizing.cpp
    nemopage.cpp
    qrc_internal_resources.cpp
    nemoimageprovider.cpp
    plugin.cpp
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
    plugin.h
    themedaemon/mlocalthemedaemonclient.h
    themedaemon/mabstractthemedaemonclient.h
    qquickfilteringmousearea.h
    nemofocussingleton.h
    nemowindow.h
    sizing.h
    nemopage.h
)

qt_add_qml_module(nemocontrols
    URI "Nemo.Controls"
    VERSION 2.0
    NO_GENERATE_PLUGIN_SOURCE
    QML_FILES
        qml/ActionButton.qml
        qml/ApplicationWindow.qml
        qml/Button.qml
        qml/ButtonRow.qml
        qml/Checkbox.qml
        qml/DatePicker.qml
        qml/dialogs
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
        qml/ToolButton.qml
        qml/Wallpaper.qml
    SOURCES
        ${SRC}
        ${HEADERS})

target_link_libraries(nemocontrols PRIVATE
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Qml
    Qt${QT_MAJOR_VERSION}::Quick
    PkgConfig::MLITE)

install(TARGETS nemocontrolsplugin
    LIBRARY DESTINATION ${QT_INSTALL_QML}/Nemo/Controls/)

install(TARGETS nemocontrols
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qmldir
    DESTINATION ${QT_INSTALL_QML}/Nemo/Controls/)
