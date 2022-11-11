set(SRC
    qquicknemostyleextensionplugin.cpp
)

set(HEADERS
    qquicknemostyleextensionplugin.h
)

add_library(nemostyleplugin SHARED ${SRC})


set(QT_LIB_LIST Core Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

target_link_libraries(nemostyleplugin
    ${QT_DEPLIBS}
)

install(TARGETS nemostyleplugin DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY qml/
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY images
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY themes
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)
