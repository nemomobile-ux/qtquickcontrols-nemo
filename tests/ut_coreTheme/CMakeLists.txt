set(TESTNAME coretheme)

set(SRC
    ut_${TESTNAME}.cpp
    ut_${TESTNAME}.h
    ${CMAKE_SOURCE_DIR}/src/core/theme.cpp
    ${CMAKE_SOURCE_DIR}/src/core/logging.cpp)

add_executable(ut_${TESTNAME} ${SRC}
    testTheme.json)

include_directories(${CMAKE_SOURCE_DIR}/src/core)

target_link_libraries(ut_${TESTNAME}
    Qt6::Core
    Qt6::Test
    Qt6::Qml
    Qt6::Gui
    PkgConfig::MLITE)

add_test(ut_${TESTNAME} ut_${TESTNAME})
