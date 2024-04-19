cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project3DSA)

set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(project3DSA main.cpp song.h
        redblacktree.h)
target_link_libraries(project3DSA sfml-system sfml-window sfml-graphics sfml-audio)
