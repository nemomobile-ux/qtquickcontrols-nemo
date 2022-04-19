
set(SRC
    calendarmodel.cpp
    plugin.cpp)

set(HEADERS
    calendarmodel.h)

add_library(nemouxmodels SHARED ${SRC})

target_link_libraries(nemouxmodels
    Qt5::Core
    Qt5::Qml 
    Qt5::Quick)

install(FILES qmldir DESTINATION ${QT_INSTALL_QML}/Nemo/UX/Models/)
install(TARGETS nemouxmodels DESTINATION ${QT_INSTALL_QML}/Nemo/UX/Models/)
