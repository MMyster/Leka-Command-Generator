cmake_minimum_required(VERSION 3.4)

project(src_leka_command_generator)

set(SOURCES    
    LKCommandGenerator.cpp
    )
    
set(HEADERS
    ../include/LKAlphaComSpecs.h
    ../include/LKCommandGenerator.h
    )

add_library(src_lkctrl ${SOURCES} ${HEADERS})