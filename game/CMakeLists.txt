project(game)

# Source files
file(GLOB_RECURSE SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    src/*.c
)

message(GAME_SOURCES=[${SOURCES}])

# Make library
add_executable(game ${SOURCES})
target_include_directories(game PRIVATE include)
target_link_libraries(game engine_loader)


add_custom_command(TARGET game POST_BUILD        # Adds a post-build event to engine_s
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
    "${engine_BINARY_DIR}/engine_dll.dll"      # <--this is in-file
    ${game_BINARY_DIR})
