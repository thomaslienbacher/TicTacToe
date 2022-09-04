cmake_minimum_required(VERSION 3.13)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    
    if (WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    endif ()
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif ()

message("Building ${PROJECT_NAME} in ${CMAKE_BUILD_TYPE} mode")

set(TICTACTOE_SRC src/main.cpp src/window.cpp src/window.hpp src/map.hpp src/map.cpp src/map.hpp src/button.cpp src/button.hpp
        src/gamescene.cpp src/gamescene.hpp src/menuscene.cpp src/menuscene.hpp src/eventhandler.hpp src/gameinfo.hpp
        src/textinput.cpp src/textinput.hpp src/networkscene.cpp src/networkscene.hpp)
add_executable(${PROJECT_NAME} ${TICTACTOE_SRC})

find_package(SFML 2.5 COMPONENTS system graphics network REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-network)

