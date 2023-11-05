project(game_proj)

# Source files
file(GLOB_RECURSE SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    src/*.c
)

message(GAME_SOURCES="${SOURCES}")

# Make library
add_executable(game ${SOURCES})
target_include_directories(game PRIVATE include)
target_link_libraries(game engine)

install(TARGETS game RUNTIME DESTINATION bin)
