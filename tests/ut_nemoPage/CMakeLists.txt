set(TESTNAME nemopage)

set(SRC
    ut_${TESTNAME}.cpp
    ut_${TESTNAME}.h
    ${CMAKE_SOURCE_DIR}/src/controls/logging.cpp
    ${CMAKE_SOURCE_DIR}/src/controls/nemopage.cpp
)

add_executable(ut_${TESTNAME} ${SRC})
add_definitions(-DQT_INSTALL_QML=".")

include_directories(${CMAKE_SOURCE_DIR}/src/controls)

target_link_libraries(ut_${TESTNAME}
    Qt6::Core
    Qt6::Test
    Qt6::Qml
    Qt6::Quick
    Qt6::Gui)

add_test(ut_${TESTNAME} ut_${TESTNAME})
