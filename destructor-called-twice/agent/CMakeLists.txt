set(TARGET agent)

add_library(${TARGET} STATIC
        agent.cpp
        token.cpp
        )

set(PUBLIC_HEADERS
        agent.h
        token.h
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        FRAMEWORK FALSE
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
        )

target_include_directories(${TARGET}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        )
