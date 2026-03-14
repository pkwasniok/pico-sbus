cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(pico_sbus)

pico_sdk_init()

add_library(pico_sbus src/sbus.c)
target_include_directories(pico_sbus PUBLIC include/)
target_link_libraries(pico_sbus pico_stdlib)

add_executable(monitor src/monitor.c)
target_link_libraries(monitor pico_stdlib pico_stdio_usb pico_sbus)

