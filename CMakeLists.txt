cmake_minimum_required(VERSION 3.4)

include_directories(/opt/CLIPP)
include_directories(./include)

project(leka_command_generator)

set(SOURCES    
    main.cpp
    )


add_subdirectory (sources)

add_executable(lkctrl ${SOURCES})

target_link_libraries(lkctrl src_lkctrl)