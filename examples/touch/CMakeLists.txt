find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC
	src/main.cpp
)

qt_add_resources(RESOURCES glacier-components.qrc)

add_executable(glacier-components ${SRC} ${RESOURCES})

add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")
target_link_libraries(glacier-components
        QT_DEPLIBS
	Glacier::App
)

install(TARGETS glacier-components RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES org.nemomobile.notify.service
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/dbus-1/services)

install(FILES glacier-components.desktop
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
