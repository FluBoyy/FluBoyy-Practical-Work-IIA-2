cmake_minimum_required(VERSION 3.26)
project(evolutivo C)

set(CMAKE_C_STANDARD 17)

include_directories(.)

add_executable(evolutivo
        algoritmo.c
        algoritmo.h
        funcao.c
        funcao.h
        main.c
        utils.c
        utils.h
        utils.c
        utils.h
        funcao.c
        funcao.h
        algoritmo.c
        algoritmo.h
)
