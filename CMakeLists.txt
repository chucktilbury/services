cmake_minimum_required(VERSION 3.18)
project(services)

#set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ./ )

add_library( ${PROJECT_NAME}
    memory.c
    ptr_list.c
    strings.c
    tree.c
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:DEBUG>:-Og>
    $<$<CONFIG:DEBUG>:-DMEMORY_DEBUG>
    $<$<CONFIG:DEBUG>:-DENA_TRACE>
    $<$<CONFIG:RELEASE>:-Ofast>
    $<$<CONFIG:PROFILE>:-pg -O0>
)

#add_subdirectory(tests)
