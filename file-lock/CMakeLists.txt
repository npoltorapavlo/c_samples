project(file-lock)

cmake_minimum_required(VERSION 3.3)

set(TARGET ${PROJECT_NAME})

add_executable(${TARGET} file-lock.cpp binarysemaphore.cpp critsection.cpp)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )
