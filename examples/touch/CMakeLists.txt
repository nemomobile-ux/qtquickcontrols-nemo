find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC	src/main.cpp)
if(QT_MAJOR_VERSION EQUAL 5)
qt5_add_resources(RESOURCES glacier-components.qrc)
else()
qt6_add_resources(RESOURCES glacier-components.qrc)
endif()

add_executable(glacier-components ${SRC} ${RESOURCES})

target_link_libraries(glacier-components
        Qt${QT_MAJOR_VERSION}::Gui
        Qt${QT_MAJOR_VERSION}::Qml
        Qt${QT_MAJOR_VERSION}::Quick
	Glacier::App
)

install(TARGETS glacier-components RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES org.nemomobile.notify.service
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/dbus-1/services)

install(FILES glacier-components.desktop
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
