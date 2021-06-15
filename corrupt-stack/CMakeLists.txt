project(corrupt-stack)
cmake_minimum_required(VERSION 3.16)

set(TARGET corrupt-stack)

find_package(Threads REQUIRED)

add_executable(${TARGET}
        corrupt-stack.cpp
        dynamicloader.cpp
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

target_link_libraries(${TARGET}
        PRIVATE
        ${CMAKE_DL_LIBS}
        Threads::Threads
        )

target_include_directories(${TARGET}
        PUBLIC
        sharedlibrary
        )

add_subdirectory(sharedlibrary)
