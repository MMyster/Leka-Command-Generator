cmake_minimum_required(VERSION 3.4)

include_directories(/opt/CLI11)

project(leka_command_generator)

set(SOURCES    
    sources/main.cpp
    sources/LKCommandGenerator.cpp
    )
    
set(HEADERS
    include/LKAlphaComSpecs.h
    include/LKCommandGenerator.h
    )

add_executable(lkctrl ${SOURCES} ${HEADERS})