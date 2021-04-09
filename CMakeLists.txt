project(1c-submission)

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    -Wfatal-errors
    -Wall -Wextra
    )

set(INCLUDE_DIR ${1c-submission_SOURCE_DIR}/inc)
set(SOURCE_DIR ${1c-submission_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

add_executable(
    solution
    ${SOURCE_DIR}/main.cpp
    )
