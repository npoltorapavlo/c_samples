project(virtual-init)
cmake_minimum_required(VERSION 3.16)

set(NAME virtual-init)

add_executable(${NAME}
        virtual-init.cpp
        )

set_target_properties(${NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        )
