project(sysinfo-test)

cmake_minimum_required(VERSION 3.3)

set(TARGET ${PROJECT_NAME})

add_executable(${TARGET} data.cpp sysutils.cpp sysinfo-test.cpp)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

install(TARGETS ${TARGET} DESTINATION bin)
