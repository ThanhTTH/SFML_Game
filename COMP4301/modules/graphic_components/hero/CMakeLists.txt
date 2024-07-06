cmake_minimum_required(VERSION 3.22)
project(hero)

list(APPEND HERO_SRS ${CMAKE_SOURCE_DIR}/modules/graphic_components/hero/hero.cpp)

add_library(${PROJECT_NAME} ${HERO_SRS})

target_link_libraries(${PROJECT_NAME} sfml-graphics)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)