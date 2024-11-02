cmake_minimum_required(VERSION 3.15.0)
project(mekosh C)

set(CMAKE_C_STANDARD 11)

set(PROJECT_SOURCES
	src/main.c
	lib/utils.h src/utils.c
)

include_directories(lib)
include_directories(src)

add_executable(mekosh ${PROJECT_SOURCE_DIR}/src/main.c)

target_sources(mekosh PRIVATE ${PROJECT_SOURCES})

target_compile_options(mekosh PRIVATE -Wall -Wextra -Wpedantic -Werror)