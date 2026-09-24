cmake_minimum_required(VERSION 3.20)
project(MyGameEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable Raylib extras & examples before FetchContent
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
    GIT_SHALLOW    TRUE # Speeds up downloading by only pulling tag depth 1
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/application.cpp
    src/resources/texture.cpp
    src/resources/sound.cpp
    src/resources/font.cpp
    src/input/input.cpp
    src/entities/player.cpp
    src/entities/wall.cpp
    src/entities/projectile.cpp
    src/entities/enemy.cpp
    src/entities/snake.cpp
    src/entities/apple.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE src)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-missing-field-initializers
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
