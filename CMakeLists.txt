cmake_minimum_required(VERSION 3.9)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

set(LIB_LOC ${CMAKE_CURRENT_SOURCE_DIR}/libs/)
set(MGW_LOC "C:/MinGW/lib/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(${LIB_LOC}sfml/include/)

add_executable(TicTacToe src/main.cpp src/sfml.hpp src/window.cpp src/window.hpp src/map.hpp src/map.cpp src/map.hpp src/button.cpp src/button.hpp src/gamescene.cpp src/gamescene.hpp src/menuscene.cpp src/menuscene.hpp src/eventhandler.hpp src/eventhandler.cpp src/gameinfo.hpp src/animation.cpp src/animation.hpp)

target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libopengl32.a)
target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libwinmm.a)
target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libgdi32.a)

target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-window.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-system.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-network.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libfreetype.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-graphics.a)
target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libopengl32.a)
