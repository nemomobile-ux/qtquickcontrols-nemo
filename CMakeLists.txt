cmake_minimum_required(VERSION 3.6.0)

project(qtquickcontrols-nemo
        VERSION 6.0.0
	DESCRIPTION "QtQuick.Controls.Nemo")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FeatureSummary)
include(GNUInstallDirs)

option(BUILD_EXAMPLES "Build the example projects" OFF)

if(NOT DEFINED QT_MAJOR_VERSION)
    set(QT_MAJOR_VERSION 5)
endif()

set(INSTALL_QML_IMPORT_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt/qml"
	CACHE PATH "Custom QML import installation directory")

if(QT_MAJOR_VERSION EQUAL 5)
set(QT_MIN_VERSION "5.11.0")
else()
set(QT_MIN_VERSION "6.0.0")
endif()

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} COMPONENTS Gui Qml Quick REQUIRED)
if(QT_MAJOR_VERSION EQUAL 5)
find_package(Qt5QuickCompiler)
endif()
find_package(PkgConfig REQUIRED)

### Sets QT_INSTALL_QML to the directory where QML Plugins should be installed
function(FindQtInstallQml)
    if(QT_MAJOR_VERSION EQUAL 5)
        find_program(QMAKE NAMES qmake-qt5 qmake)
    else()
        find_program(QMAKE NAMES qmake-qt6 qmake6)
    endif()
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

add_subdirectory(src)
if(BUILD_EXAMPLES)
add_subdirectory(examples)
endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
