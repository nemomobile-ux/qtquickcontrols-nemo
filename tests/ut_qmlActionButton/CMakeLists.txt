set(TESTNAME qmlactionbutton)

set(SRC
    ut_${TESTNAME}.cpp
    ut_${TESTNAME}.h
    ${COMMON_SRC}
)

add_executable(ut_${TESTNAME} ${SRC}
    test.qml)

target_link_libraries(ut_${TESTNAME}
    Qt6::Core
    Qt6::Test
    Qt6::Qml
    Qt6::Quick
    Qt6::Gui)

add_test(NAME ut_${TESTNAME} COMMAND "xvfb-run" ${xvfbParam} ${CMAKE_BINARY_DIR}/tests/ut_qmlActionButton/ut_${TESTNAME})
