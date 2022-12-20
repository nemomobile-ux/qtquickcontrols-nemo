find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC	main.cpp)

if(QT_MAJOR_VERSION EQUAL 5)
qt5_add_resources(RESOURCES glacier-sizeview.qrc)
else()
qt6_add_resources(RESOURCES glacier-sizeview.qrc)
endif()
add_executable(glacier-sizeview ${SRC} ${RESOURCES})

target_link_libraries(glacier-sizeview
        Qt${QT_MAJOR_VERSION}::Gui
        Qt${QT_MAJOR_VERSION}::Qml
        Qt${QT_MAJOR_VERSION}::Quick
	Glacier::App
)

install(TARGETS glacier-sizeview RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
