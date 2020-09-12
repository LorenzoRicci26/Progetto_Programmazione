cmake_minimum_required(VERSION 3.16)
project(UNTITLED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(Google_Test)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SOURCE_FILES main.cpp Subject.h Observer.h Gamecharacter.h Gamecharacter.cpp TileMap.h TileMap.cpp stlastar.h fsa.h Utility.cpp Utility.h MapSearchNode.cpp MapSearchNode.h)
add_executable(UNTITLED main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-graphics sfml-audio)
target_link_libraries(UNTITLED core)




