project(wpeframework-test)

cmake_minimum_required(VERSION 3.8)

set(TARGET wpeframework-test)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

find_package(PkgConfig)
find_package(Threads REQUIRED)
find_package(WPEFramework REQUIRED)

add_executable(${TARGET}
        wpeframework-test.cpp
        thunderaccess.cpp
        systemclient.cpp
        processinfo.cpp
        )

if (WPEFRAMEWORK_FOUND)
    target_include_directories(${TARGET} PRIVATE ${WPEFRAMEWORK_INCLUDE_DIRS})
    target_link_libraries(${TARGET} PRIVATE ${WPEFRAMEWORK_LIBRARIES})
else()
    message(FATAL_ERROR "WPEFramework not found")
endif()

target_link_libraries(${TARGET} PRIVATE -lpthread)

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)
