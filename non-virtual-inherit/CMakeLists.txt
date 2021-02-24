set(NAME non-virtual-inherit)

add_executable(${NAME} non-virtual-inherit.cpp)

set_target_properties(${NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

install(TARGETS ${NAME} DESTINATION bin)
