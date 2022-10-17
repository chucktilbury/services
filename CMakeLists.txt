cmake_minimum_required(VERSION 3.18)
project(_services)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_BUILD_TYPE release)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${LIBRARY_OUTPUT_PATH}")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${EXECUTABLE_OUTPUT_PATH}")
include_directories( ${CMAKE_CURRENT_BINARY_DIR} ./ )
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/clangformat-cmake/cmake)
include(ClangFormat)
#target_clangformat_setup(src)

add_custom_target(format-src
    COMMENT "Format the source code"
    COMMAND clang-format -i *.c *.h
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
)

add_custom_target(format-tests
    COMMENT "Format the tests"
    COMMAND clang-format -i *.c *.h
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
