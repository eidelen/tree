cmake_minimum_required(VERSION 3.0.0)
project(tree VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(TESTTREE  "TEST" ON)
IF(${TESTTREE})
    MESSAGE(STATUS "Tests activated")
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    FILE(GLOB_RECURSE  TESTS_SRC        test/*.cpp)

    add_executable(runTreeTests ${TESTS_INC} ${TESTS_SRC})

    set(LIBSTOLINK  )
    if (NOT WIN32)
        set(LIBSTOLINK pthread)
    endif (WIN32)

    target_link_libraries(runTreeTests ${GTEST_LIBRARIES} ${LIBSTOLINK} )
    target_compile_features( runTreeTests PRIVATE cxx_range_for )
ENDIF()

