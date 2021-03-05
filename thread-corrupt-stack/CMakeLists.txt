project(thread-corrupt-stack)
cmake_minimum_required(VERSION 3.16)

set(TARGET thread-corrupt-stack)

add_executable(${TARGET}
        thread-corrupt-stack.cpp
        dynamicloader.cpp
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

target_link_libraries(${TARGET}
        PRIVATE
        ${CMAKE_DL_LIBS}
        )

target_include_directories(${TARGET}
        PUBLIC
        sharedlibrary
        )

add_subdirectory(sharedlibrary)
