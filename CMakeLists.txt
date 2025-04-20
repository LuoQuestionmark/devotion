cmake_minimum_required(VERSION 3.15.0)
project(devotion VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_COMPILER "gcc")

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(SDL2 REQUIRED)

include_directories(include)

# main executable
add_executable(main
    src/devotion.c
    src/gameplay/board.c
    src/gameplay/title.c
    src/gameplay/game_event.c
    src/gameplay/god_intervention.c
    src/gameplay/god_intervention_impl.c
    src/gameplay/player.c
    src/gameplay/elements/rain.c
    src/gameplay/elements/food.c
    src/gameplay/elements/amant.c
    src/gui/callback.c
    src/gui/gui_amant.c
    src/gui/gui_board.c
    src/gui/gui_title.c
    src/gui/gui_god_intervention.c
)
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES} m)

add_executable(title_test
    src/gameplay/title.c
    test/title_test.c
)
