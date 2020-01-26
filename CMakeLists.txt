cmake_minimum_required(VERSION 3.15)
project(ArcadeApp)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories(App Games Utils Graphics Shapes Scenes Input Assets ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "App/*.cpp" "Games/*.cpp" "Games/BreakOut/*.cpp" "Utils/*.cpp"
        "Graphics/*.cpp" "Shapes/*.cpp" "Scenes/*.cpp" "Input/*.cpp")

add_executable(ArcadeApp main.cpp ${SOURCES})
target_link_libraries(ArcadeApp ${SDL2_LIBRARIES})