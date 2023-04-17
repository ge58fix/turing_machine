cmake_minimum_required(VERSION 3.25)
project(turing_machine C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(turing_machine
        src/main.c
        src/tape.c
        src/tape.h
        src/tm.c
        src/tm.h
        src/transition.h
        src/transitions.c
        src/transitions.h
        src/state_list.h
        src/state_list.c)
