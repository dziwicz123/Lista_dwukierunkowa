cmake_minimum_required(VERSION 3.16)
project(lista_dwukierunkowa C)

set(CMAKE_C_STANDARD 23)

add_compile_options(
        "-ggdb3"
        "-xc"
        "-fdiagnostics-color"
        "-pedantic"
        "-Werror"
        "-Wall"
        "-Wextra"
        "-fmax-errors=5"
        "-Werror=vla"
        "-Wno-error=unused-parameter"
        "-Wno-error=implicit-fallthrough"
        "-Wno-error=parentheses"
        "-Wno-parentheses"
        "-D_GNU_SOURCE"
)
add_executable(lista_dwukierunkowa
        main.c
        defs.c defs.h)

target_link_libraries(lista_dwukierunkowa
        "m"
        )