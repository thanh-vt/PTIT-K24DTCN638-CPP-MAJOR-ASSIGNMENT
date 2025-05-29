cmake_minimum_required(VERSION 3.31)
project(homework-K24DTCN638)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fully static linking
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(K24DTCN638_VuTatThanh_BT01 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT01.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT02 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT02.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT03 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT03.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT04 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT04.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT05 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT05.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT06 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT06.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT07 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT07.cpp"
        src/util.cpp
        include/util.h)
add_executable(K24DTCN638_VuTatThanh_BT08 "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT08.cpp"
        src/util.cpp
        include/util.h)

target_include_directories(K24DTCN638_VuTatThanh_BT01 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT02 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT03 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT04 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT05 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT06 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT07 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(K24DTCN638_VuTatThanh_BT08 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB TEST_FILES
        "${CMAKE_SOURCE_DIR}/test/*.txt"
)

file(COPY ${TEST_FILES} DESTINATION ${CMAKE_BINARY_DIR})