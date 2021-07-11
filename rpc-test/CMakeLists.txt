project(rpc-test)

cmake_minimum_required(VERSION 3.8)

add_executable(rpc-test rpc-test.cpp)

target_link_libraries(rpc-test PRIVATE authclient)

install(TARGETS rpc-test DESTINATION bin)

find_package(WPEFramework)
find_package(${NAMESPACE}Core REQUIRED)
find_package(${NAMESPACE}COM REQUIRED)
find_package(${NAMESPACE}Plugins REQUIRED)

add_library(authclient SHARED authclient.cpp Module.cpp)

target_link_libraries(authclient
        PUBLIC
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${NAMESPACE}COM::${NAMESPACE}COM
        )

set_target_properties(authclient PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS authclient DESTINATION lib)
