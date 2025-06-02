cmake_minimum_required(VERSION 3.31)
project(homework-K24DTCN638)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fully static linking
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Define common source files
set(COMMON_SOURCES
    src/util.cpp
    include/util.h
)

# Set the number of exercises
set(NUM_EXERCISES 27)

# Generate exercise numbers from 01 to NUM_EXERCISES
set(EXERCISE_NUMBERS "")
foreach(I RANGE 1 ${NUM_EXERCISES})
    string(REGEX REPLACE "^([0-9])$" "0\\1" I_PADDED "${I}")
    list(APPEND EXERCISE_NUMBERS ${I_PADDED})
endforeach()

# Loop through exercise numbers to create executables
foreach(NUM ${EXERCISE_NUMBERS})
    add_executable(K24DTCN638_VuTatThanh_BT${NUM} 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/K24DTCN638_VuTatThanh_BT${NUM}.cpp"
        ${COMMON_SOURCES}
    )
    
    target_include_directories(K24DTCN638_VuTatThanh_BT${NUM} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endforeach()

# Copy test files
file(GLOB TEST_FILES
    "${CMAKE_SOURCE_DIR}/test/**"
)
file(COPY ${TEST_FILES} DESTINATION ${CMAKE_BINARY_DIR})