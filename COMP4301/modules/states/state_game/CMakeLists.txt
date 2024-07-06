cmake_minimum_required(VERSION 3.22)
project (state_game)

list(APPEND STATE_GAME ${CMAKE_SOURCE_DIR}/modules/states/state_game/state_game.cpp)

add_library(${PROJECT_NAME} STATIC ${STATE_GAME})

target_link_libraries(${PROJECT_NAME} sfml-graphics 
                                      utilitis 
                                      event_manager
                                      state_manager
                                      background
                                      enemy
                                      hero
                                      rocket
                                      sky
                                    )

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/modules/event_manager
    ${CMAKE_SOURCE_DIR}/modules/states/state_game
    ${CMAKE_SOURCE_DIR}/modules/states/state_manager
    ${CMAKE_SOURCE_DIR}/modules/utilitis
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/hero
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/enemy
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/rocket
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/sky
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/background
)