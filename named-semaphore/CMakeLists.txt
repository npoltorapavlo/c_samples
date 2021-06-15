project(named-semaphore)

cmake_minimum_required(VERSION 3.3)

set(TARGET ${PROJECT_NAME})

find_package(Threads REQUIRED)

add_executable(${TARGET} named-semaphore.cpp semaphore.cpp critsection.cpp)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

target_link_libraries(${TARGET} PRIVATE Threads::Threads)
