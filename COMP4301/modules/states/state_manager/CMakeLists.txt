cmake_minimum_required(VERSION 3.22)
project (state_manager)

list(APPEND STATE_MANAGER ${CMAKE_SOURCE_DIR}/modules/states/state_manager/state_manager.cpp)

add_library(${PROJECT_NAME} STATIC ${STATE_MANAGER})

target_link_libraries(${PROJECT_NAME} sfml-graphics 
                                        state_mainmenu
                                        state_game
                                    )

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/modules/states/state_mainmenu
    ${CMAKE_SOURCE_DIR}/modules/states/state_game
)