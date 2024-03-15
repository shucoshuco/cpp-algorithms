cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GCC_COMPILE_FLAGS "-std=gnu++2a")

Include(FetchContent)

project(
  cmake_autobuild
  VERSION 1.0.0
  LANGUAGES CXX
)

if(NOT DEFINED CATCH2_VERSION)
    set(CATCH2_VERSION
        v3.0.1
        CACHE
        STRING "Version of Catch2 (https://github.com/catchorg/Catch2) used for unit testing."
    )
endif()


FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        ${CATCH2_VERSION} # or a later release
)

FetchContent_MakeAvailable(
    Catch2
)

# Library

set(
    LIB_INC_DIR
    ${CMAKE_SOURCE_DIR}/lib/inc
)

set(
    LIB_SRC_DIR
    ${CMAKE_SOURCE_DIR}/lib/src
)

add_library(
    lib
    ${LIB_SRC_DIR}/graph.cpp
    ${LIB_SRC_DIR}/avl.cpp
    ${LIB_SRC_DIR}/btree.cpp
    ${LIB_SRC_DIR}/trie.cpp
    ${LIB_SRC_DIR}/heap.cpp
    ${LIB_SRC_DIR}/utils.cpp
)

target_include_directories(lib PUBLIC "${LIB_INC_DIR}")

# Library tests

set(
    LIB_TEST_DIR
    ${CMAKE_SOURCE_DIR}/lib/tests
)

add_executable(lib_tests
               ${LIB_TEST_DIR}/test_graph.cpp
               ${LIB_TEST_DIR}/test_avl.cpp
               ${LIB_TEST_DIR}/test_btree.cpp
               ${LIB_TEST_DIR}/test_trie.cpp
               ${LIB_TEST_DIR}/test_heap.cpp
               ${LIB_TEST_DIR}/test_btree.cpp
               ${LIB_TEST_DIR}/test_utils.cpp
)

target_include_directories(lib_tests PUBLIC "${LIB_INC_DIR}")

target_link_libraries(lib_tests
    PRIVATE
        lib
        Catch2::Catch2WithMain
)


# Application

set(
    INC_DIR
    ${CMAKE_SOURCE_DIR}/inc
)

set(
    SRC_DIR
    ${CMAKE_SOURCE_DIR}/src
)

add_executable(
    app_lib
    ${SRC_DIR}/main.cpp
)

target_include_directories(app_lib PUBLIC "${INC_DIR}" "${LIB_INC_DIR}")

target_link_libraries(app_lib
    PRIVATE
        lib
        Catch2::Catch2WithMain
)


# Application tests

set(
    TEST_DIR
    ${CMAKE_SOURCE_DIR}/tests
)

add_executable(tests
               ${TEST_DIR}/test_main.cpp
)

target_include_directories(tests PUBLIC "${INC_DIR}" "${LIB_INC_DIR}")

target_link_libraries(tests
    PRIVATE
        lib
        Catch2::Catch2WithMain
)