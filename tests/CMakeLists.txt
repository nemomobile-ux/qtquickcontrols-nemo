add_definitions(-DUNIT_TEST=1)
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")
add_subdirectory(ut_coreTheme)
add_subdirectory(ut_imageProvider)
