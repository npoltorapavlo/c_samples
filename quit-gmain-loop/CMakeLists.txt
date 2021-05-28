project(quit-gmain-loop)
cmake_minimum_required(VERSION 3.16)

set(TARGET quit-gmain-loop)
set(TARGET_PLUGIN plugin)
set(TARGET_SERVICES services)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)

add_executable(${TARGET}
        quit-gmain-loop.cpp
        dynloader.cpp
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

target_link_libraries(${TARGET}
        PRIVATE
        ${CMAKE_DL_LIBS}
        Threads::Threads
        services
        )

add_library(${TARGET_PLUGIN} SHARED
        plugin.cpp
        pluginthread.cpp
        )

target_include_directories(${TARGET_PLUGIN} PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_directories(${TARGET_PLUGIN} PRIVATE ${GLIB_LIBRARY_DIRS})
target_link_libraries(${TARGET_PLUGIN} PRIVATE ${GLIB_LIBRARIES} services)

set_target_properties(${TARGET_PLUGIN} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        FRAMEWORK FALSE
        PUBLIC_HEADER plugin.h
        )

add_library(${TARGET_SERVICES} SHARED
        service.cpp
        )

set_target_properties(${TARGET_SERVICES} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        FRAMEWORK FALSE
        PUBLIC_HEADER "service.h"
        )
