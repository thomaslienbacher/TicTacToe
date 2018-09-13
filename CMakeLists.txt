cmake_minimum_required(VERSION 3.9)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

set(LIB_LOC ${CMAKE_CURRENT_SOURCE_DIR}/libs/)
set(MGW_LOC "C:/MinGW/lib/")

include_directories(${LIB_LOC}sfml/include/)

add_executable(TicTacToe src/main.cpp src/sfml.hpp src/window.cpp src/window.hpp src/logiccontroller.cpp src/logiccontroller.hpp src/gameinfo.cpp src/gameinfo.hpp src/drawcontroller.cpp src/drawcontroller.hpp src/gameobjects/ma.hpp src/gameobjects/map.cpp src/gameobjects/map.hpp)

target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libopengl32.a)
target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libwinmm.a)
target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libgdi32.a)

target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-window.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-system.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-network.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libfreetype.a)
target_link_libraries(${PROJECT_NAME} ${LIB_LOC}sfml/libsfml-graphics.a)
target_link_libraries(${PROJECT_NAME} ${MGW_LOC}libopengl32.a)
