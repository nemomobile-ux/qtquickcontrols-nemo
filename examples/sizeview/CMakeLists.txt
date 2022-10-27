find_package(Glacier 0.8 COMPONENTS App REQUIRED)

set(SRC
	main.cpp
)

qt_add_resources(RESOURCES glacier-sizeview.qrc)

add_executable(glacier-sizeview ${SRC} ${RESOURCES})

add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")
target_link_libraries(glacier-sizeview
        QT_DEPLIBS
	Glacier::App
)

install(TARGETS glacier-sizeview RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
