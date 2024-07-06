cmake_minimum_required(VERSION 3.22)
project(background)

list(APPEND BACKGROUND_SRC ${CMAKE_SOURCE_DIR}/modules/graphic_components/background/background.cpp)

add_library(${PROJECT_NAME} ${BACKGROUND_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)