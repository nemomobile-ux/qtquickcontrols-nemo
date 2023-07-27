set(QML
    qml/CustomDialog.qml
    qml/Dialog.qml
    qml/QueryDialog.qml
    qml/SelectionDialog.qml)

qt6_add_qml_module(nemodialogsplugin
    URI Nemo.Dialogs
    VERSION 2.0
    PLUGIN_TARGET nemodialogsplugin
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${SOURCES}
        ${HEADERS}
    QML_FILES
        ${QML}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Nemo/Dialogs
)

install(TARGETS nemodialogsplugin
    RUNTIME DESTINATION "${QT_INSTALL_QML}/Nemo/Dialogs"
    BUNDLE DESTINATION "${QT_INSTALL_QML}/Nemo/Dialogs"
    LIBRARY DESTINATION "${QT_INSTALL_QML}/Nemo/Dialogs"
)

install(DIRECTORY qml/
    DESTINATION ${QT_INSTALL_QML}/Nemo/Dialogs)
