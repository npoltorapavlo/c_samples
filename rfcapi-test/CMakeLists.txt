project(rfcapi-test)

cmake_minimum_required(VERSION 3.8)

set(TARGET ${PROJECT_NAME})

add_executable(${TARGET}
        rfcapi-test.cpp
        rfcutils.cpp
        textgen.cpp
        )

target_link_libraries(${TARGET} PRIVATE rfcapi)

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)
