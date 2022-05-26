cmake_minimum_required(VERSION 3.6.0)

project(qtquickcontrols-nemo
        VERSION 5.7.0
	DESCRIPTION "QtQuick.Controls.Nemo")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FeatureSummary)
include(GNUInstallDirs)

set(INSTALL_QML_IMPORT_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt/qml"
	CACHE PATH "Custom QML import installation directory")

set(QT_MIN_VERSION "5.11.0")
find_package(Qt5 ${QT_MIN_VERSION} COMPONENTS Gui Qml Quick REQUIRED)
find_package(Qt5QuickCompiler)
find_package(PkgConfig REQUIRED)

### Sets QT_INSTALL_QML to the directory where QML Plugins should be installed
function(FindQtInstallQml)
    find_program(QMAKE NAMES qmake-qt5 qmake)
    if(NOT QMAKE)
        message(FATAL_ERROR "qmake not found")
    endif()
    execute_process(
        COMMAND ${QMAKE} -query QT_INSTALL_QML
        OUTPUT_VARIABLE PROC_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(QT_INSTALL_QML ${PROC_RESULT} PARENT_SCOPE)
endfunction()

FindQtInstallQml()

add_subdirectory(examples)
add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
