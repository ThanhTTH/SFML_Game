cmake_minimum_required(VERSION 3.22)
project (state_mainmenu)

list(APPEND STATE_MAINMENU ${CMAKE_SOURCE_DIR}/modules/states/state_mainmenu/state_mainmenu.cpp)

add_library(${PROJECT_NAME} STATIC ${STATE_MAINMENU})

target_link_libraries(${PROJECT_NAME} sfml-graphics 
                                        utilitis 
                                        event_manager
                                        state_manager
                                        background
                                    )

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd-party/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/modules/event_manager
    ${CMAKE_SOURCE_DIR}/modules/graphic_components/background
    ${CMAKE_SOURCE_DIR}/modules/states/state_manager
    ${CMAKE_SOURCE_DIR}/modules/utilitis
)