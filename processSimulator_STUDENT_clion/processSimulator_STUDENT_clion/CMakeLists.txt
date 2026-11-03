cmake_minimum_required(VERSION 3.30)
project(processSimulator_STUDENT_clion C)

set(CMAKE_C_STANDARD 11)

include_directories(processSimulator)

add_executable(processSimulator_STUDENT_clion
    processSimulator/main.c
    processSimulator/processManagement.c
    processSimulator/processManagement.h
    processSimulator/processTestCode.c
    processSimulator/processTestCode.h)
