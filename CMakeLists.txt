cmake_minimum_required(VERSION 3.15.0)
project(devotion VERSION 0.1.0 LANGUAGES C)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(SDL2 REQUIRED)

include_directories(include)

# main executable
add_executable(main
    src/devotion.c
    src/board.c
    src/callback.c
    src/gui/gui_board.c
)
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES} m)
