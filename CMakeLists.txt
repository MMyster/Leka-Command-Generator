cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 20)

include_directories(./clipp)
include_directories(./include)

project(leka_command_generator)

set(SOURCES
    main.cpp
    )


add_subdirectory (sources)

add_executable(lkctrl ${SOURCES})

target_link_libraries(lkctrl src_lkctrl)
