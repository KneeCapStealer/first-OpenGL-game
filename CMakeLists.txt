cmake_minimum_required(VERSION "3.27.7")

project(first_game)

# Compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)

# Compiler options and preprocessor defines
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wpedantic)
endif()

# dont suggest '_s' functions
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_subdirectory(engine)
add_subdirectory(game)
