cmake_minimum_required(VERSION 3.10.0)
project(devotion VERSION 0.1.0 LANGUAGES C)

find_package(SDL2 REQUIRED)

include_directories(include)

# test olive.c working condition
add_executable(test src/triangleTex.c)
target_include_directories(test PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(test ${SDL2_LIBRARIES} m)

# main executable
add_executable(main
    src/devotion.c
    src/board.c
)
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES} m)
