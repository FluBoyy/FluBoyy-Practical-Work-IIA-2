cmake_minimum_required(VERSION 3.26)
project(Meta2 C)

set(CMAKE_C_STANDARD 17)

include_directories(.)

add_executable(Meta2
        algoritmo.c
        algoritmo.h
        funcao.c
        funcao.h
        main.c
        utils.c
        utils.h
        )
