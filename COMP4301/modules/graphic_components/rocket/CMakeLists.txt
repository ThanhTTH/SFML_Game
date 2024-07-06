cmake_minimum_required(VERSION 3.22)
project(rocket)

list(APPEND ROCKET_SRC ${CMAKE_SOURCE_DIR}/modules/graphic_components/rocket/rocket.cpp)

add_library(${PROJECT_NAME} ${ROCKET_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/3rd-party/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)