find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC
	main.cpp
)

qt6_add_resources(RESOURCES glacier-sizeview.qrc)

add_executable(glacier-sizeview ${SRC} ${RESOURCES})

target_link_libraries(glacier-sizeview
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        PkgConfig::GLACIER
)

install(TARGETS glacier-sizeview RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
