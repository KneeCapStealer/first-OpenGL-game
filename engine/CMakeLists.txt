project(engine)

# Source files
file(GLOB_RECURSE SOURCES
    RELATIVE ${engine_SOURCE_DIR}
    src/*.c
)

add_library(engine_dll SHARED ${SOURCES})
target_include_directories(engine_dll PRIVATE include PUBLIC interface INTERFACE include/GLFW)

target_link_libraries(engine_dll ${PROJECT_SOURCE_DIR}/lib/glfw3.lib)
target_link_libraries(engine_dll ${PROJECT_SOURCE_DIR}/lib/glad.lib)
target_link_libraries(engine_dll opengl32)

file(INSTALL
    "${engine_BINARY_DIR}/engine_dll.dll"
    DESTINATION "${CMAKE_BINARY_DIR}/game"
)
