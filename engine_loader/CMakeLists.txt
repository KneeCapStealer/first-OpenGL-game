project(engine_loader)

file(GLOB_RECURSE LOAD_SOURCES
    RELATIVE ${engine_loader_SOURCE_DIR}
    src/*.c
)

add_library(engine_loader STATIC ${LOAD_SOURCES})
target_include_directories(engine_loader PUBLIC interface)
target_link_libraries(engine_loader engine_dll)
