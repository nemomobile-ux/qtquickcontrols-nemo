set(TESTNAME imageprovider)

set(SRC
    ut_${TESTNAME}.cpp
    ut_${TESTNAME}.h
    ${CMAKE_SOURCE_DIR}/src/core/logging.cpp
    ${CMAKE_SOURCE_DIR}/src/core/nemoimageprovider.cpp
    ${CMAKE_SOURCE_DIR}/src/core/themedaemon/mlocalthemedaemonclient.cpp
    ${CMAKE_SOURCE_DIR}/src/core/themedaemon/mabstractthemedaemonclient.cpp)

add_executable(ut_${TESTNAME} ${SRC})
add_definitions(-DQT_INSTALL_QML=".")

include_directories(${CMAKE_SOURCE_DIR}/src/core)

target_link_libraries(ut_${TESTNAME}
    Qt6::Core
    Qt6::Test
    Qt6::Qml
    Qt6::Quick
    Qt6::Gui
    PkgConfig::MLITE)

add_test(ut_${TESTNAME} ut_${TESTNAME})
