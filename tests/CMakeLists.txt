
project(tests)

# add_custom_command( TARGET tests
#     COMMAND clang -c tree.c
# )

add_executable( ${PROJECT_NAME}
    tree.c
    array.c
    list.c
    memory.c
    strings.c
    tree.c
    harness.c
)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")

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

target_link_libraries(${PROJECT_NAME}
    services
)
