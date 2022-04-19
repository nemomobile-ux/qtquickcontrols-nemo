set(SRC
    qquicknemostyleextensionplugin.cpp
)

set(HEADERS
    qquicknemostyleextensionplugin.h
)

add_library(nemostyleplugin SHARED ${SRC})

target_link_libraries(nemostyleplugin
    Qt5::Core
    Qt5::Qml 
    Qt5::Quick
)

install(TARGETS nemostyleplugin DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY qml/
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY images
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)

install(DIRECTORY themes
        DESTINATION ${QT_INSTALL_QML}/QtQuick/Controls/Styles/Nemo/)
