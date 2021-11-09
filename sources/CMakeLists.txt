cmake_minimum_required(VERSION 3.4)

include_directories(/opt/CLI11)

project(src_leka_command_generator)

set(SOURCES    
    LKCommandGenerator.cpp
    )
    
set(HEADERS
    ../include/LKAlphaComSpecs.h
    ../include/LKCommandGenerator.h
    )

add_library(src_lkctrl ${SOURCES} ${HEADERS})