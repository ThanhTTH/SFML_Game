cmake_minimum_required(VERSION 3.22)
project(graphic_components)

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/graphic_components/background background)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/graphic_components/enemy enemy)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/graphic_components/hero hero)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/graphic_components/rocket rocket)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/graphic_components/sky sky)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/graphic_components/window window)