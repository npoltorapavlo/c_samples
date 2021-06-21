project(file-lock)

cmake_minimum_required(VERSION 3.3)

set(TARGET ${PROJECT_NAME})
set(CRASH_TEST file-lock-crashtest)

add_executable(${TARGET} file-lock.cpp binarysemaphore.cpp critsection.cpp)
add_executable(${CRASH_TEST} file-lock-crashtest.cpp binarysemaphore.cpp critsection.cpp)

set_target_properties(${TARGET} ${CRASH_TEST} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

install(TARGETS ${TARGET} ${CRASH_TEST} DESTINATION bin)
