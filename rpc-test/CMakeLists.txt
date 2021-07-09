project(rpc-test)

cmake_minimum_required(VERSION 3.8)

set(TARGET ${PROJECT_NAME})

find_package(WPEFramework)
find_package(${NAMESPACE}Core REQUIRED)
find_package(${NAMESPACE}COM REQUIRED)
find_package(${NAMESPACE}Plugins REQUIRED)

add_executable(${TARGET}
        rpc-test.cpp
        server.cpp
        client.h
        )

target_link_libraries(${TARGET}
        PUBLIC
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${NAMESPACE}COM::${NAMESPACE}COM
        ${NAMESPACE}Plugins::${NAMESPACE}Plugins
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)
