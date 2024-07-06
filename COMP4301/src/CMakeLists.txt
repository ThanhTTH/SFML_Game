cmake_minimum_required(VERSION 3.22)
project(game_object)

list(APPEND SET_UP_SRC ${CMAKE_SOURCE_DIR}/src/source.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/modules modules)

add_executable(${PROJECT_NAME} ${SET_UP_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics window game)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_SOURCE_DIR}/modules/game
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/hero
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/enemy
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/rocket
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/window
)