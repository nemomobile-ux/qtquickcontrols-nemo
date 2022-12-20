set(SRC
    qquicknemostyleextensionplugin.cpp
)

set(HEADERS
    qquicknemostyleextensionplugin.h
)

add_library(nemostyleplugin SHARED ${SRC})

target_link_libraries(nemostyleplugin
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Qml
    Qt${QT_MAJOR_VERSION}::Quick
)

install(TARGETS nemostyleplugin DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY qml/
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY images
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY themes
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)
