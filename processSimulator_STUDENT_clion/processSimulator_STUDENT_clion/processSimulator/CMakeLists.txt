cmake_minimum_required(VERSION 3.30)
project(processSimulator C)

set(CMAKE_C_STANDARD 11)

add_executable(processSimulator main.c
        processTestCode.h
        processTestCode.c
        processManagement.c
        processManagement.h)
