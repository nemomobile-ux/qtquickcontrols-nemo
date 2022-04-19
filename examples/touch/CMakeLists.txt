find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC
	src/main.cpp
)

qtquick_compiler_add_resources(RESOURCES glacier-components.qrc)

add_executable(glacier-components ${SRC} ${RESOURCES})

target_link_libraries(glacier-components
	Qt5::Gui
	Qt5::Qml
	Qt5::Quick
	Glacier::App
)

install(TARGETS glacier-components RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES org.nemomobile.notify.service
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/dbus-1/services)

install(FILES glacier-components.desktop
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
