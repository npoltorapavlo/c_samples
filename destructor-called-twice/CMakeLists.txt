project(destructor-called-twice)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(agent)
add_subdirectory(lib)
add_subdirectory(a)
add_subdirectory(b)
add_subdirectory(app)
