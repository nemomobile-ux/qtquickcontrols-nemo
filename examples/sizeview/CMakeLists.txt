find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC
	main.cpp
)

qtquick_compiler_add_resources(RESOURCES glacier-sizeview.qrc)

add_executable(glacier-sizeview ${SRC} ${RESOURCES})

target_link_libraries(glacier-sizeview
	Qt5::Gui
	Qt5::Qml
	Qt5::Quick
	Glacier::App
)

install(TARGETS glacier-sizeview RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
