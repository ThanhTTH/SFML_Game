cmake_minimum_required(VERSION 3.22)
project(game)

list(APPEND GAME_SRC ${CMAKE_SOURCE_DIR}/modules/game/game.cpp)

add_library(${PROJECT_NAME} STATIC ${GAME_SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics 
                                        window
                                        event_manager 
                                        state_manager
                                    )

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/modules/utilitis
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/window
)