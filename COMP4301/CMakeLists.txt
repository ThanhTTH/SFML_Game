cmake_minimum_required(VERSION 3.22)
project(setup)


set(CMAKE_INSTALL_RPATH "./")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
# 
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath-link,${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-rpath-link,${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "-Wl,-rpath-link,${CMAKE_MODULE_LINKER_FLAGS}")

set(SFML_DIR "${CMAKE_SOURCE_DIR}/3rd-party/SFML/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/src src)