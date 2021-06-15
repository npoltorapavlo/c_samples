set(TARGET app)

add_executable(${TARGET} app.cpp)

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

target_link_libraries(${TARGET}
        PRIVATE
        a
        b
        )