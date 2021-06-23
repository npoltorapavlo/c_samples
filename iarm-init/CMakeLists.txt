project(iarm-init)

cmake_minimum_required(VERSION 3.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

set(TARGET ${PROJECT_NAME})

add_executable(${TARGET}
        iarm-init.cpp
        iarmutils.cpp
        )

find_package(IARMBus REQUIRED)
target_include_directories(${TARGET} PRIVATE ${IARMBUS_INCLUDE_DIRS})
target_link_libraries(${TARGET} PRIVATE ${IARMBUS_LIBRARIES})

find_package(Threads REQUIRED)
target_link_libraries(${TARGET} PRIVATE Threads::Threads)

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)
