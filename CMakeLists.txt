cmake_minimum_required(VERSION 3.6.0)

project(qtquickcontrols-nemo
        VERSION 5.7.0
	DESCRIPTION "QtQuick.Controls.Nemo")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FeatureSummary)
include(GNUInstallDirs)
include(QtVersionCompat)

set(INSTALL_QML_IMPORT_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt/qml"
	CACHE PATH "Custom QML import installation directory")

set(QT_MIN_VERSION "5.11.0")
set(QT_LIB_LIST Gui Qml Quick)
find_qt_package( "${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

if(!USE_QT6)
find_package(Qt5QuickCompiler)
endif()

find_package(PkgConfig REQUIRED)

### Sets QT_INSTALL_QML to the directory where QML Plugins should be installed
function(FindQtInstallQml)
    find_program(QMAKE NAMES qmake-qt${QT_PKG_VER} qmake)
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

option(BUILD_CONTROLS "Build the controls" ON)
option(BUILD_EXAMPLES "Build the example projects" OFF)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_CONTROLS)
    add_subdirectory(src)
endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
