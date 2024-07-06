cmake_minimum_required(VERSION 3.22)
project(enemy)

list(APPEND ENEMY_SRC ${CMAKE_SOURCE_DIR}/modules/graphic_components/enemy/enemy.cpp)

add_library(${PROJECT_NAME} ${ENEMY_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)