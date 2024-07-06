cmake_minimum_required(VERSION 3.22)
project(states)

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/states/state_mainmenu state_mainmenu)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/states/state_manager state_manager)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/states/state_game state_game)
