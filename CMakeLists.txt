cmake_minimum_required(VERSION 3.13)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_USAGE TicTacToe) #use one [TicTacToe, AiTraining]

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -mwindows")
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif ()
message("Building ${PROJECT_NAME} as ${BUILD_USAGE} in ${CMAKE_BUILD_TYPE} mode")

if (${BUILD_USAGE} STREQUAL TicTacToe)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(TICTACTOE_SRC src/main.cpp src/window.cpp src/window.hpp src/map.hpp src/map.cpp src/map.hpp src/button.cpp src/button.hpp
            src/gamescene.cpp src/gamescene.hpp src/menuscene.cpp src/menuscene.hpp src/eventhandler.hpp src/gameinfo.hpp
            src/textinput.cpp src/textinput.hpp src/networkscene.cpp src/networkscene.hpp)
    add_executable(${PROJECT_NAME} ${TICTACTOE_SRC})
elseif (${BUILD_USAGE} STREQUAL AiTraining)
    include_directories(${LIB_LOC}SimpleNeuralNetwork/src/)
    add_subdirectory(libs/SimpleNeuralNetwork)
    set(AITRAINING_SRC src/aitraining/aitraining.cpp src/aitraining/board.cpp src/aitraining/board.hpp)
    add_executable(${PROJECT_NAME} ${AITRAINING_SRC})
    target_link_libraries(${PROJECT_NAME} SimpleNeuralNetwork)
endif ()

find_package(PkgConfig)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-network)

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
