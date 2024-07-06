cmake_minimum_required(VERSION 3.22)
project(event_manager)

list(APPEND EVENT_MANAGER_SRC ${CMAKE_SOURCE_DIR}/modules/event_manager/event_manager.cpp)

add_library(${PROJECT_NAME} STATIC ${EVENT_MANAGER_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics utilitis)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/modules/utilitis
)