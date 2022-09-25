cmake_minimum_required(VERSION 3.20)
project(RAYLIB_PONG)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(RLUT_DIR ${CMAKE_SOURCE_DIR}/src/rlut)
set(ENTT_DIR ${CMAKE_SOURCE_DIR}/vendor/ENTT)
set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/vendor/RAYLIB)

add_subdirectory(${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/pong)
