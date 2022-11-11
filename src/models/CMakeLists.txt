
set(SRC
    calendarmodel.cpp
    plugin.cpp)

set(HEADERS
    calendarmodel.h)

add_library(nemouxmodels SHARED ${SRC})

set(QT_LIB_LIST Core Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")


target_link_libraries(nemouxmodels
    ${QT_DEPLIBS}
)

install(FILES qmldir DESTINATION ${QT_INSTALL_QML}/Nemo/UX/Models/)
install(TARGETS nemouxmodels DESTINATION ${QT_INSTALL_QML}/Nemo/UX/Models/)
