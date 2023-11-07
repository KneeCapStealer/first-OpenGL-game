project(engine)

# Source files
file(GLOB_RECURSE SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    src/*.c
)

message(ENGINE_SOURCES="${SOURCES}")

# Make library
add_library(engine STATIC ${SOURCES})
target_include_directories(engine PRIVATE include INTERFACE interface)

# Link GLFW
target_link_libraries(engine ${engine_SOURCE_DIR}/lib/glfw3dll.lib)
target_link_libraries(engine opengl32)

install(TARGETS engine LIBRARY DESTINATION lib)
