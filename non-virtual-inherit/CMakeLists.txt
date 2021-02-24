set(NAME non-virtual-inherit)

add_executable(${NAME} non-virtual-inherit.cpp)

set_target_properties(${NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

if(BUILD_WITH_VIRTUAL)
    message("Building with virtual")
    add_definitions (-DUSE_VIRTUAL)
endif()
