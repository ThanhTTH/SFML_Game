cmake_minimum_required(VERSION 3.22)
project(window)

list(APPEND WINDOW_SRC ${CMAKE_SOURCE_DIR}/modules/graphic_components/window/window.cpp)

add_library(${PROJECT_NAME} STATIC ${WINDOW_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics event_manager)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)