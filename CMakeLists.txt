cmake_minimum_required(VERSION 3.31)
project(homework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fully static linking
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

file(GLOB HOMEWORK_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(homework ${HOMEWORK_SRC})

target_include_directories(homework PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
