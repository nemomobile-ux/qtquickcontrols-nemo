set(TESTNAME qmlapplicationwindow)

set(SRC
    ut_${TESTNAME}.cpp
    ut_${TESTNAME}.h
    ${COMMON_SRC}
)

add_definitions(-DQT_QML_DEBUG=1)

add_executable(ut_${TESTNAME} ${SRC}
    test.qml)

include_directories(${CMAKE_SOURCE_DIR}/tests/common)

target_link_libraries(ut_${TESTNAME}
    Qt6::Core
    Qt6::Test
    Qt6::Qml
    Qt6::Quick
    Qt6::Gui)

add_test(NAME ut_${TESTNAME} COMMAND "xvfb-run" ${xvfbParam} ${CMAKE_BINARY_DIR}/tests/ut_qmlApplicationWindow/ut_${TESTNAME})
