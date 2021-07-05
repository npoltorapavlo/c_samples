project(jsonrpc-test)

cmake_minimum_required(VERSION 3.8)

set(TARGET ${PROJECT_NAME})

find_package(PkgConfig)
find_package(Threads REQUIRED)
find_package(WPEFramework)
find_package(${NAMESPACE}Core REQUIRED)
find_package(${NAMESPACE}Tracing REQUIRED)
find_package(${NAMESPACE}Plugins REQUIRED)
find_package(${NAMESPACE}Protocols REQUIRED)
find_package(${NAMESPACE}SecurityUtil REQUIRED)

add_executable(${TARGET}
        jsonrpc-test.cpp
        )

target_link_libraries(${TARGET} PRIVATE
        -lpthread
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${NAMESPACE}Tracing::${NAMESPACE}Tracing
        ${NAMESPACE}Plugins::${NAMESPACE}Plugins
        ${NAMESPACE}Protocols::${NAMESPACE}Protocols
        ${NAMESPACE}SecurityUtil::${NAMESPACE}SecurityUtil
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)