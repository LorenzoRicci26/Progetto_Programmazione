cmake_minimum_required(VERSION 3.16)
project(UNTITLED)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(UNTITLED findpath.cpp fsa.h stlastar.h Subject.h Observer.h)

target_link_libraries(UNTITLED sfml-system sfml-window sfml-graphics)