set(TARGET sharedlibrary)

add_library(${TARGET} SHARED
        sharedlibrary.cpp
        )

set(PUBLIC_HEADERS
        sharedlibrary.h
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

if(JOIN_THREAD_ON_EXIT)
    add_definitions (-DJOIN_THREAD_ON_EXIT)
endif()
